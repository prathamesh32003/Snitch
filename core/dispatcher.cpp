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
#include "ascii.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>

namespace {
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

int get_ascii_length(std::string ascii) {
  int visible = 0;
  bool in_ansi = false;
  for (auto i : ascii) {
    if (i == '\033')
      in_ansi = true;
    else if (i == 'm' && in_ansi)
      in_ansi = false;
    else if (!in_ansi)
      visible += 1;
  }
  return visible;
}

int get_max_ascii_length(std::vector<std::string> ascii) {
  int max = 0;
  for (auto i : ascii) {
    max = std::max(max, get_ascii_length(i));
  }
  return max;
}

std::vector<std::string> get_stats(std::vector<std::string> keys) {
  std::vector<std::string> print_stats;
  for (std::string key : keys) {
    if (auto stat = actionMap.find(key); stat != actionMap.end()) {
      for (auto i : stat->second()) {
        std::vector<std::string> colors = COLOR::get_colors();
        print_stats.push_back(colors[0] + key + ": \033[0m" + colors[1] + i +
                              "\033[0m\n");
      }
    }
  }
  return print_stats;
}

} // namespace

void Dispatcher::run(std::vector<std::string> keys) {
  std::vector<std::string> ascii = ASCII::get_ascii_art();
  int max_ascii_length = get_max_ascii_length(ascii);
  std::vector<std::string> stats = get_stats(keys);
  int max_lines = std::max(ascii.size(), stats.size());
  int separator = 5;

  for (int i = 0; i < max_lines; i += 1) {
    if (i < ascii.size()) {
      std::cout << ascii[i];
      int padding = max_ascii_length - get_ascii_length(ascii[i]) + separator;
      std::cout << std::string(padding, ' ');
    } else {
      std::cout << std::string(separator + max_ascii_length, ' ');
    }

    if (i < stats.size()) {
      std::cout << stats[i];
    }
  }
}
