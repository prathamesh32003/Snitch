#pragma once

#include <string>
#include <vector>
class Config {
public:
  Config(const std::string filepath);
  std::vector<std::string> get_enabled_stats();

private:
  std::vector<std::string> enabled_stats;
  void load_from_file(const std::string filepath);
  void create_default_config(std::string filepath);
};
