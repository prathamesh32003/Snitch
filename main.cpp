#include "config/config.h"
#include "stats/battery/battery.h"
#include "stats/cpu/cpu.h"
#include "stats/desktop/desktop.h"
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
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int main(int argc, char *argv[]) {
  std::string path = getenv("HOME");
  path += "/.config/Snitch/Snitch.conf";

  Config config("/home/knight/.config/Snitch/Snitch.conf");
  std::vector<std::string> enabled_stats = config.get_enabled_stats();

  const std::unordered_map<std::string, std::function<std::string()>>
      actionMap = {
          {"user", []() { return USER::print(); }},
          {"host", []() { return HOST::print(); }},
          {"uptime", []() { return UPTIME::print(); }},
          {"os", []() { return OS::print(); }},
          {"kernel", []() { return KERNEL::print(); }},
          {"desktop", []() { return DESKTOP::print(); }},
          {"terminal", []() { return TERMINAL::print(); }},
          {"shell", []() { return SHELL::print(); }},
          {"packages", []() { return PACKAGES::print(); }},
          {"gpu", []() { return GPU::print(); }},
          {"cpu", []() { return CPU::print(); }},
          {"battery", []() { return BATTERY::print(); }},
          {"memory", []() { return MEMORY::print(); }},
          {"disk", []() { return DISK::print(); }},
      };

  for (const auto stat : enabled_stats) {
    auto it = actionMap.find(stat);
    if (it != actionMap.end()) {
      std::cout << it->second() << "\n";
    }
  }
}
