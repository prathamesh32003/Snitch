#include "GPU.h"

std::string GPU::get_gpu_names() {
  FILE *fp = popen("vulkaninfo | grep 'GPU id : '", "r");
  char path[235];
  std::string gpus = "";
  if (fp == NULL) {
    return "Failed to run command\n";
  }

  while (fgets(path, sizeof(path), fp) != NULL) {
    std::string s = path;
    if (s.find("llvm") != std::string::npos) {
      break;
    }
    gpus += s.substr(12, s.find('[') - 14) + "\n";
  }

  pclose(fp);

  return gpus;
}
