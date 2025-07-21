#include "os.h"
#include "../../utils/utils.cpp"
#include <fstream>

std::string OS::get_os_name() {
  std::ifstream getinfo("/etc/os-release");
  std::string s;

  while (std::getline(getinfo, s)) {
    if (s.substr(0, 11) == "PRETTY_NAME") {
      s.pop_back();
      return trim(s.substr(s.find("=") + 2));
    }
  }
  return "Unable to get OS name";
}
