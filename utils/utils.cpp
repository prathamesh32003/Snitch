#include "utils.h"

std::string trim(const std::string str) {
  const size_t first = str.find_first_not_of(" \t\n\r");
  if (first == std::string::npos)
    return "";
  const size_t last = str.find_last_not_of(" \t\n\r");
  return str.substr(first, last - first + 1);
}
