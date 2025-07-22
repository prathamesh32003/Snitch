#include "kernel.h"
#include "../../utils/utils.h"
#include <sys/utsname.h>

std::string KERNEL::print() {
  struct utsname osInfo{};
  uname(&osInfo);
  return trim(osInfo.release);
}
