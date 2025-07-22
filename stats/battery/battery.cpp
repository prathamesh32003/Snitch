#include "battery.h"
#include "../../utils/utils.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
namespace fs = std::filesystem;

std::string BATTERY::print() {
  std::string path = "/sys/class/power_supply/";
  for (const auto &entry : fs::directory_iterator(path)) {
    std::string name = entry.path().filename().string();
    if (name.rfind("BAT", 0) == 0) {
      std::ifstream file(entry.path() / "capacity");
      if (!file.is_open()) {
        std::cerr << "Failed to open: " << (entry.path() / "capacity") << "\n";
        continue;
      }

      std::string battery_level;
      std::getline(file, battery_level);
      return trim(battery_level + "%");
    }
  }

  return "unknown";
}
