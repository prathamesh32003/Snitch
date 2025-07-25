#include "shell.h"
#include "../../utils/utils.h"
#include <fstream>
#include <unistd.h>

std::string SHELL::get() {
  pid_t shell_id = getppid();
  std::string path = "/proc/" + std::to_string(shell_id) + "/status";
  std::ifstream file(path);

  // Finding the parent of this program (usually shell like bash)
  std::string line;
  int term_id;
  while (std::getline(file, line)) {
    if (line.rfind("Name:", 0) == 0) {
      std::string value = line.substr(line.find(":") + 1);
      int start = value.find_first_not_of("\t");
      return trim(value.substr(start));
    }
  }

  return "unknown";
}
