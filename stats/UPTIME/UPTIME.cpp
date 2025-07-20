#include "UPTIME.h"
#include <chrono>
#include <fstream>

std::string UPTIME::get_uptime() {
  std::chrono::milliseconds uptime(0u);
  double uptime_seconds;
  if (std::ifstream("/proc/uptime", std::ios::in) >> uptime_seconds) {
    uptime = std::chrono::milliseconds(
        static_cast<unsigned long long>(uptime_seconds * 1000.0));
  }

  std::string hours = std::to_string((int)uptime_seconds / 3600) + "H ";
  std::string minutes = std::to_string((int)uptime_seconds % 3600 / 60) + "M";

  return hours + minutes;
}
