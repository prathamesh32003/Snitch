#include "memory.h"
#include "../../utils/utils.h"
#include <fstream>
#include <sstream>
#include <string>

std::string MEMORY::get_total_memory() {
  std::ifstream getinfo("/proc/meminfo");
  if (!getinfo.is_open()) {
    return "Unknown";
  }

  std::string line, result;
  while (std::getline(getinfo, line)) {
    if (line.rfind("MemTotal:", 0) == 0) {
      std::istringstream iss(line);
      std::string key;
      long kb;
      iss >> key >> kb;
      long mb = kb / 1000;
      result += std::to_string(mb) + " MB";
      break;
    }
  }

  return trim(result);
}
