#include "config.h"
#include "../utils/utils.h"
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

void copy_ascii_files(const std::string configpath) {
  namespace fs = std::filesystem;
  fs::path configdir = configpath;
  if (!fs::exists(configdir / "ascii")) {
    fs::create_directories(configdir / "ascii");

    for (const auto &file :
         fs::directory_iterator("/usr/local/share/snitch/ascii/")) {
      if (file.is_regular_file()) {
        fs::copy_file(file.path(), configdir / "ascii" / file.path().filename(),
                      fs::copy_options::skip_existing);
      }
    }
  }
}

Config::Config(const std::string filepath) {
  namespace fs = std::filesystem;
  fs::path configPath(filepath);
  if (!fs::exists(configPath)) {
    fs::path dir = configPath.parent_path();
    if (!fs::exists(dir)) {
      fs::create_directories(dir);
    }
    create_default_config(configPath);
  }

  copy_ascii_files(configPath.parent_path().string());

  load_from_file(filepath);
}

void Config::create_default_config(const std::string configPath) {
  std::string content = "# The order of content here is the same way it will "
                        "display in your terminal\n"
                        "USER\n"
                        "HOST\n"
                        "UPTIME\n"
                        "OS\n"
                        "KERNEL\n"
                        "DESKTOP\n"
                        "TERMINAL\n"
                        "SHELL\n"
                        "# PACKAGES # Resource Intensive\n"
                        "# GPU # Resource Intensive\n"
                        "CPU\n"
                        "BATTERY\n"
                        "MEMORY\n"
                        "DISK\n";
  std::ofstream configFile(configPath);
  configFile << content;
  configFile.close();
}

void Config::load_from_file(std::string filepath) {
  std::ifstream configFile(filepath);
  std::string line;

  while (std::getline(configFile, line)) {
    if (line[0] == '#' || line.empty())
      continue;

    auto comment_pos = line.find("#");
    if (comment_pos != std::string::npos) {
      line = line.substr(0, comment_pos);
    }
    Config::enabled_stats.push_back(trim(line));
  }
}

std::vector<std::string> Config::get_enabled_stats() {
  return Config::enabled_stats;
}
