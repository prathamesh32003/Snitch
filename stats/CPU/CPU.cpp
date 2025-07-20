#include "CPU.h"
#include <fstream>

std::string CPU::get_cpu_name() {
  std::ifstream getinfo("/proc/cpuinfo");
  std::string s;

  while (std::getline(getinfo, s)) {
    if (s.substr(0, 10) == "model name") {
      return s.substr(s.find(":") + 2);
      break;
    }
  }

  return "";
}
