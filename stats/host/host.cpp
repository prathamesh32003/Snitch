#include "host.h"
#include "../../utils/utils.h"

std::string HOST::print() { return trim(getenv("HOSTNAME")); }
