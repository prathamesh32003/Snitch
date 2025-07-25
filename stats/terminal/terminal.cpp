#include "terminal.h"
#include "../../utils/utils.h"
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>

std::string TERMINAL::get() {
  pid_t shell_id = getppid();
  std::string path = "/proc/" + std::to_string(shell_id) + "/status";
  std::ifstream file(path);

  // Finding the parent of this program (usually shell like bash)
  std::string line;
  int term_id;
  while (std::getline(file, line)) {
    if (line.rfind("PPid:", 0) == 0) {
      std::istringstream iss(line);
      std::string key;
      iss >> key >> term_id;
      break;
    }
  }
  file.close();

  // Finding parent of shell (usually terminal)
  path = "/proc/" + std::to_string(term_id) + "/status";
  file.open(path);
  while (std::getline(file, line)) {
    if (line.rfind("Name:", 0) == 0) {
      std::string value = line.substr(line.find(":") + 1);
      int start = value.find_first_not_of("\t");
      return trim(value.substr(start));
    }
  }
  return "unknown";
}
