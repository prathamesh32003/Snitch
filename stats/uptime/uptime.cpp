#include "uptime.h"
#include "../../utils/utils.h"
#include <chrono>
#include <fstream>

std::vector<std::string> UPTIME::get() {
  double uptime_seconds = 0.0;
  std::ifstream uptime_file("/proc/uptime");

  if (!uptime_file.is_open()) {
    return {"unknown"};
  }

  if (!(uptime_file >> uptime_seconds)) {
    return {"unknown"};
  }

  auto uptime = std::chrono::milliseconds(
      static_cast<unsigned long long>(uptime_seconds * 1000.0));

  std::string hours =
      std::to_string(static_cast<int>(uptime_seconds) / 3600) + "H ";
  std::string minutes =
      std::to_string(static_cast<int>(uptime_seconds) % 3600 / 60) + "M";

  return {trim(hours + minutes)};
}
