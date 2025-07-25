#include "color.h"
#include <random>
#include <string>
#include <vector>

std::vector<int> baseColors = {27, 33, 39, 45, 51,  69,  75,
                               81, 87, 93, 99, 105, 111, 117};

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dist(0, baseColors.size());

std::vector<std::string> Color::get_colors() {
  std::vector<std::string> colors;
  int base = baseColors[gen() % baseColors.size()];
  std::string label = "\033[1;38;5;" + std::to_string(base) + "m";
  std::string value = "\033[;38;5;" + std::to_string(base) + "m";

  colors.push_back(label);
  colors.push_back(value);

  return colors;
}
