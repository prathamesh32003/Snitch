#include "config.h"
#include "../utils/utils.h"
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

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

  load_from_file(filepath);
}

void Config::create_default_config(const std::string configPath) {
  std::string content = "# The order of content here is the same way it will "
                        "display in your terminal\n"
                        "user\n"
                        "host\n"
                        "uptime\n"
                        "os\n"
                        "kernel\n"
                        "desktop\n"
                        "terminal\n"
                        "shell\n"
                        "# packages # Resource Intensive\n"
                        "# gpu # Resource Intensive\n"
                        "cpu\n"
                        "battery\n"
                        "memory\n"
                        "disk\n";
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
