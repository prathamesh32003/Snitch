#include "user.h"
#include "../../utils/utils.h"

std::string USER::get_user_name() { return trim(getenv("USER")); }
