#include "disk.h"
#include "../../utils/utils.h"
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
namespace fs = std::filesystem;

std::string DISK::get() {
  std::error_code ec;
  auto space = fs::space("/", ec);

  if (ec) {
    return "unknown";
  }

  constexpr long GB = 1024 * 1024 * 1024;

  long total = space.capacity / GB;
  long used = (space.capacity - space.free) / GB;
  long percent = (static_cast<double>(used) / total) * 100;

  std::ostringstream oss;
  oss << used << "/" << total << " GB (" << percent << "%)";

  return trim(oss.str());
}
