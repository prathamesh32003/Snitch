#include "cpu.h"
#include "../../utils/utils.h"
#include <fstream>

std::string CPU::get_cpu_name() {
  std::ifstream getinfo("/proc/cpuinfo");
  std::string s, result;

  while (std::getline(getinfo, s)) {
    if (s.substr(0, 10) == "model name") {
      return trim(s.substr(s.find(":") + 2));
      break;
    }
  }

  return "";
}
