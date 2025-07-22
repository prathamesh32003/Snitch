#include "packages.h"
#include "../../utils/utils.h"
#include <array>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <stdexcept>
#include <string>

namespace {

bool command_exists(std::string cmd) {
  std::string check = "command -v " + cmd + " > /dev/null 2>&1";
  return !(std::system((check).c_str()));
}

std::string run_command(const std::string cmd) {
  std::array<char, 128> buffer{};
  std::string result;

  FILE *pipe = popen(cmd.c_str(), "r");
  if (!pipe)
    throw std::runtime_error("popen() failed");

  while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
    result += buffer.data();
  }
  pclose(pipe);

  return result;
}

} // namespace

std::string PACKAGES::print() {
  const std::map<std::string, std::string> managers = {
      {"apx", "apx list -i | wc -l"},
      {"eopkg", "eopkg list-installed | wc -l"},
      {"scratchpkg", "scratch installed | wc -l"},
      {"sorcery", "gaze installed | wc -l"},
      {"slpkg", "ls /var/log/packages | wc -l"},
      {"guix", "guix package --list-installed | wc -l"},
      {"pkgutils", "pkginfo -i | wc -l"},
      {"nix", "nix-env --query --installed | wc -l"},
      {"xbps", "xbps-query -l | wc -l"},
      {"emerge", "equery list '*' | wc -l"},
      {"dnf", "rpm -qa | wc -l"},
      {"yum", "yum list installed | wc -l"},
      {"apt", "dpkg-query -l | grep '^ii' | wc -l"},
      {"zypper", "rpm -qa --last | wc --l"},
      {"pacman", "pacman -Q | wc -l"},
      {"apk", "apk list --installed | wc -l"},
      {"pkg", "pkg info"},
      {"pkgsrc", "pkg_info"},
      {"homebrew", "brew list | wc -l"},
  };

  for (const auto &[manager, cmd] : managers) {
    if (command_exists(manager)) {
      return trim(run_command(cmd));
    }
  }
  return "unknown";
}
