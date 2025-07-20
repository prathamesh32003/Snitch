#include "KERNEL.h"
#include <sys/utsname.h>

std::string KERNEL::get_kernel_name() {
  struct utsname osInfo{};
  uname(&osInfo);
  return osInfo.release;
}
