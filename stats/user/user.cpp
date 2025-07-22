#include "user.h"
#include "../../utils/utils.h"

std::string USER::print() {
  std::string result = std::getenv("USER");
  if (result.length() == 0)
    return "unknown";
  return trim(result);
}
