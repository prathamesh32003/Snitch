#include "host.h"
#include "../../utils/utils.h"

std::string HOST::get_host_name() { return trim(getenv("HOSTNAME")); }
