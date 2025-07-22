#include "memory.h"
#include "../../utils/utils.h"
#include <fstream>
#include <sstream>
#include <string>

std::string MEMORY::print() {
  std::ifstream getinfo("/proc/meminfo");
  if (!getinfo.is_open()) {
    return "Unknown";
  }

  std::string line;
  long total = -1, used = -1, percent;
  while (std::getline(getinfo, line)) {
    if (line.rfind("MemTotal:", 0) == 0) {
      std::istringstream iss(line);
      std::string key;
      long kb;
      iss >> key >> kb;
      total = kb / 1000;
    }
    if (line.rfind("MemFree", 0) == 0) {
      std::istringstream iss(line);
      std::string key;
      long kb;
      iss >> key >> kb;
      long available = kb / 1000;
      used = total - available;
    }
    if (total != -1 && used != -1) {
      percent = (static_cast<double>(used) / total) * 100;
    }
  }

  std::ostringstream oss;
  oss << used << "/" << total << " MB (" << percent << "%)";
  return trim(oss.str());
}
