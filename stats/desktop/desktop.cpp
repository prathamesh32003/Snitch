#include "desktop.h"
#include "../../utils/utils.h"
#include <cstdlib>
#include <cstring>

std::vector<std::string> DESKTOP::get() {
  std::string result = "";

  result = getenv("XDG_CURRENT_DESKTOP");

  if (result == "")
    result = getenv("XDG_SESSION_DESKTOP");

  if (result == "")
    result = getenv("DESKTOP_SESSION");

  if (result == "") {
    if (strcmp(getenv("XDG_SESSION_TYPE"), "tty") == 0)
      result = "Headless";
  }

  if (result == "")
    result = "Unknown";

  return {trim(result)};
}
