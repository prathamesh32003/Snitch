#include "disk.h"
#include "../../utils/utils.h"
#include <filesystem>
#include <iostream>
#include <string>
namespace fs = std::filesystem;

std::string DISK::get_disk_space() {
  std::error_code ec;
  auto space = fs::space("/", ec);

  if (ec) {
    std::cerr << "Error getting disk space: " << ec.message() << "\n";
    return "Error";
  }

  float total = space.capacity / (1024.0 * 1024.0 * 1024.0);
  float used = (space.capacity - space.free) / (1024.0 * 1024.0 * 1024.0);
  float percent = (used / total) * 100;

  return std::to_string(int(used)) + "/" + std::to_string(int(total)) +
         " GB (" + std::to_string(int(percent)) + "%)";
}
