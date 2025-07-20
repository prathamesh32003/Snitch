#include "HOST.h"

std::string HOST::get_host_name() { return getenv("HOSTNAME"); }
