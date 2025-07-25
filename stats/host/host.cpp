#include "host.h"
#include "../../utils/utils.h"
#include <cstdlib>

std::string HOST::get() {
  std::string result = std::getenv("HOSTNAME");
  if (result.length() == 0)
    return "unknown";
  return trim(result);
}
