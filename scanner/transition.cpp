#include "transition.h"


#pragma optimize("", off)

transition::transition(char_class const& cl, std::string const& target_state)
    : class_(cl), target_state_(target_state) {}


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
