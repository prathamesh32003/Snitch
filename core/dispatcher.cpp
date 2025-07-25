#include "dispatcher.h"
#include "../stats/battery/battery.h"
#include "../stats/cpu/cpu.h"
#include "../stats/desktop/desktop.h"
#include "../stats/disk/disk.h"
#include "../stats/gpu/gpu.h"
#include "../stats/host/host.h"
#include "../stats/kernel/kernel.h"
#include "../stats/memory/memory.h"
#include "../stats/os/os.h"
#include "../stats/packages/packages.h"
#include "../stats/shell/shell.h"
#include "../stats/terminal/terminal.h"
#include "../stats/uptime/uptime.h"
#include "../stats/user/user.h"
#include "../utils/color.h"
#include <functional>
#include <iostream>
#include <unordered_map>

const std::unordered_map<std::string, std::function<std::vector<std::string>()>>
    actionMap = {
        {"USER", []() { return USER::get(); }},
        {"HOST", []() { return HOST::get(); }},
        {"UPTIME", []() { return UPTIME::get(); }},
        {"OS", []() { return OS::get(); }},
        {"KERNEL", []() { return KERNEL::get(); }},
        {"DESKTOP", []() { return DESKTOP::get(); }},
        {"TERMINAL", []() { return TERMINAL::get(); }},
        {"SHELL", []() { return SHELL::get(); }},
        {"PACKAGES", []() { return PACKAGES::get(); }},
        {"GPU", []() { return GPU::get(); }},
        {"CPU", []() { return CPU::get(); }},
        {"BATTERY", []() { return BATTERY::get(); }},
        {"MEMORY", []() { return MEMORY::get(); }},
        {"DISK", []() { return DISK::get(); }},
};

void Dispatcher::run(std::string key) {
  std::vector<std::string> colors = Color::get_colors(), print_stats;
  if (auto it = actionMap.find(key); it != actionMap.end()) {
    for (auto i : it->second()) {
      print_stats.push_back(colors[0] + key + ": \033[0m" + colors[1] + i +
                            "\033[0m\n");
    }
  }
  for (auto it : print_stats)
    std::cout << it;
}
