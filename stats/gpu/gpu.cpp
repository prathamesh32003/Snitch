#include "gpu.h"
#include <cstdio>
#include <regex>
#include <sstream>
#include <string>

std::vector<std::string> GPU::get() {
  std::vector<std::string> gpu_array;
  FILE *pipe = popen("vulkaninfo 2>/dev/null | grep 'GPU id : '", "r");
  if (!pipe) {
    return {"unknown"};
  }

  std::ostringstream gpus;
  char buffer[512];

  std::regex gpu_regex(R"(GPU id\s*:\s*\d+\s*\((.*)\))");

  while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
    std::string line(buffer);

    std::smatch match;
    if (std::regex_search(line, match, gpu_regex)) {
      std::string name = match[1];

      // Ignore software renderers (e.g. LLVM)
      if (name.find("llvm") != std::string::npos ||
          name.find("llvmpipe") != std::string::npos ||
          name.find("Software") != std::string::npos) {
        break;
      }

      gpu_array.push_back(name);
    }
  }

  pclose(pipe);

  return gpu_array;
}
