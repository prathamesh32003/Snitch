#include "kernel.h"
#include "../../utils/utils.h"
#include <string>
#include <sys/utsname.h>

std::string KERNEL::get() {
  struct utsname osInfo{};
  uname(&osInfo);

  std::string result = osInfo.release;
  if (result.length() == 0) {
    return "unknown";
  }
  return trim(osInfo.release);
}
