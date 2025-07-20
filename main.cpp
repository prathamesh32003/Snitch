#include "stats/CPU/CPU.h"
#include "stats/GPU/GPU.h"
#include "stats/HOST/HOST.h"
#include "stats/KERNEL/KERNEL.h"
#include "stats/OS/OS.h"
#include "stats/UPTIME/UPTIME.h"
#include "stats/USER/USER.h"
#include <iostream>

int main(int argc, char *argv[]) {
  CPU cpu;
  std::cout << cpu.get_cpu_name() << std::endl;

  GPU gpu;
  std::cout << gpu.get_gpu_names() << std::endl;

  OS os;
  std::cout << os.get_os_name() << std::endl;

  HOST host;
  std::cout << host.get_host_name() << std::endl;

  UPTIME uptime;
  std::cout << uptime.get_uptime() << std::endl;

  USER user;
  std::cout << user.get_user_name() << std::endl;

  KERNEL kernel;
  std::cout << kernel.get_kernel_name() << std::endl;
  return 0;
}
