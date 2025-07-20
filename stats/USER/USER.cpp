#include "USER.h"

std::string USER::get_user_name() { return getenv("USER"); }
