#include "config/config.h"
#include "core/dispatcher.h"
#include <cstdlib>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  std::string path = getenv("HOME");
  path += "/.config/Snitch/Snitch.conf";

  Config config("/home/knight/.config/Snitch/Snitch.conf");
  std::vector<std::string> enabled_stats = config.get_enabled_stats();

  for (const auto stat : enabled_stats) {
    Dispatcher::run(stat);
  }
}
