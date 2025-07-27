#include "ascii.h"
#include <cstdio>
#include <fstream>
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
      {"(WE)", "\033[37m"},   {"(BE)", "\033[34m"},
      {"(RD)", "\033[31m"}, //(..) is normal foreground
      {"(GN)", "\033[32m"},   {"(BK)", "\033[30m"},
      {"(CN)", "\033[36m"},   {"(YW)", "\033[33m"},
      {"(MA)", "\033[35m"},   {"{WE}", "\033[37;1m"},
      {"{BE}", "\033[34;1m"}, {"{RD}", "\033[31;1m"},
      {"{GN}", "\033[32;1m"}, //{..} is bright foreground
      {"{BK}", "\033[30;1m"}, {"{CN}", "\033[36;1m"},
      {"{YW}", "\033[33;1m"}, {"{MA}", "\033[35;1m"},
      {"[WE]", "\033[47m"},   {"[BE]", "\033[44m"},
      {"[RD]", "\033[41m"},   {"[GN]", "\033[42m"},
      {"[BK]", "\033[40m"}, //[..] is normal background
      {"[CN]", "\033[46m"},   {"([YW]", "\033[43m"},
      {"[MA]", "\033[45m"},   {"<WE>", "\033[47;1m"},
      {"<BE>", "\033[44;1m"}, {"<RD>", "\033[41;1m"},
      {"<GN>", "\033[42;1m"}, {"<BK>", "\033[40;1m"},
      {"<CN>", "\033[46;1m"}, //<..> is bring background
      {"<YW>", "\033[43;1m"}, {"<MA>", "\033[45;1m"},
      {"!DT!", "\033[0m"}};

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
  // std::ifstream ascii_file("../ascii/" + get_distro_id() + ".txt");
  std::ifstream ascii_file("../ascii/ubuntu.txt");
  std::vector<std::string> art;
  std::string line;
  while (std::getline(ascii_file, line)) {
    art.push_back(replace_colors(line));
  }

  return art;
}
