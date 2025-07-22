#include "os.h"
#include "../../utils/utils.cpp"
#include <fstream>

std::string OS::print() {
  std::ifstream getinfo("/etc/os-release");
  std::string s;

  while (std::getline(getinfo, s)) {
    if (s.substr(0, 11) == "PRETTY_NAME") {
      s.pop_back();
      return trim(s.substr(s.find("=") + 2));
    }
  }
  return "unknown";
}
