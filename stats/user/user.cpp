#include "user.h"
#include "../../utils/utils.h"

std::string USER::print() { return trim(getenv("USER")); }
