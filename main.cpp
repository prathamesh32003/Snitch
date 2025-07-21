#include "stats/battery/battery.h"
#include "stats/cpu/cpu.h"
#include "stats/disk/disk.h"
#include "stats/gpu/gpu.h"
#include "stats/host/host.h"
#include "stats/kernel/kernel.h"
#include "stats/memory/memory.h"
#include "stats/os/os.h"
#include "stats/packages/packages.h"
#include "stats/shell/shell.h"
#include "stats/terminal/terminal.h"
#include "stats/uptime/uptime.h"
#include "stats/user/user.h"
#include <iostream>

int main(int argc, char *argv[]) {
  std::cout << CPU::get_cpu_name() << std::endl;

  // std::cout << GPU::get_gpu_names() << std::endl;

  std::cout << OS::get_os_name() << std::endl;

  std::cout << HOST::get_host_name() << std::endl;

  std::cout << UPTIME::get_uptime() << std::endl;

  std::cout << USER::get_user_name() << std::endl;

  std::cout << KERNEL::get_kernel_name() << std::endl;

  std::cout << PACKAGES::get_total_packages() << std::endl;

  std::cout << MEMORY::get_total_memory() << std::endl;

  std::cout << TERMINAL::get_terminal_name() << std::endl;

  std::cout << SHELL::get_shell_name() << std::endl;

  std::cout << BATTERY::get_battery() << std::endl;

  std::cout << DISK::get_disk_space() << std::endl;
  return 0;
}
