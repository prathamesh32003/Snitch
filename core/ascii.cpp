#include "ascii.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace {
std::string get_distro_id() {
  std::ifstream getfile("/etc/os-release");
  std::string line;
  while (std::getline(getfile, line)) {
    if (line.rfind("ID=", 0) == 0) {
      std::string id = line.substr(3); // remove ID:
      if (!id.empty() && id.front() == '"')
        id.erase(0, 1);
      if (!id.empty() && id.back() == '"')
        id.pop_back();
      return id;
    }
  }
  return "default";
}

std::string replace_colors(std::string line) {
  const std::unordered_map<std::string, std::string> colorMap = {
      {"(BE)", "\033[34m"}, {"(WE)", "\033[37m"}, {"(RD)", "\033[31m"},
      {"(GN)", "\033[32m"}, {"(YB)", "\033[33m"}, {"(RS)", "\033[0m"}};

  std::string result = line;
  for (const auto &[tag, code] : colorMap) {
    size_t pos = 0;
    while ((pos = result.find(tag, pos)) != std::string::npos) {
      result.replace(pos, tag.length(), code);
      pos += code.length();
    }
  }
  return result + "\033[0m";
}
} // namespace

std::vector<std::string> ASCII::get_ascii_art() {
  std::ifstream getascii("../ascii/ascii.txt");
  std::string target = "### " + get_distro_id();
  std::string line;
  bool collecting = false;
  std::vector<std::string> art;
  while (getline(getascii, line)) {
    if (!collecting) {
      if (line == target)
        collecting = true;
    } else {
      if (line == "### end")
        break;
      art.push_back(replace_colors(line));
    }
  }
  return art;
}
