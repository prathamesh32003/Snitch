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
#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <unordered_map>

const std::unordered_map<std::string, std::function<std::string()>> actionMap =
    {
        {"user", []() { return USER::get(); }},
        {"host", []() { return HOST::get(); }},
        {"uptime", []() { return UPTIME::get(); }},
        {"os", []() { return OS::get(); }},
        {"kernel", []() { return KERNEL::get(); }},
        {"desktop", []() { return DESKTOP::get(); }},
        {"terminal", []() { return TERMINAL::get(); }},
        {"shell", []() { return SHELL::get(); }},
        {"packages", []() { return PACKAGES::get(); }},
        {"gpu", []() { return GPU::get(); }},
        {"cpu", []() { return CPU::get(); }},
        {"battery", []() { return BATTERY::get(); }},
        {"memory", []() { return MEMORY::get(); }},
        {"disk", []() { return DISK::get(); }},
};

void Dispatcher::run(std::string key) {
  std::vector<std::string> colors = Color::get_colors();
  if (auto it = actionMap.find(key); it != actionMap.end()) {
    std::transform(key.begin(), key.end(), key.begin(), ::toupper);
    std::cout << colors[0] << key << ": \033[0m" << colors[1] << it->second()
              << "\033[0m\n";
  }
}
