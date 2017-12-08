#include "transition.h"



transition::transition()
{
}


transition::~transition()
{
}

bool transition::is_usable(char c) const
{
    return class_.belongs(c);
}

std::string const& transition::get_target() const
{
    return target_state_;
}
