#include "state_base.h"
#include "state_err.h"
#include <algorithm>

void state_base::add_transition(transition const& trans)
{
    transitions_.push_back(trans);
}

void state_base::set_name(std::string const& name)
{
    name_ = name;
}

std::string const& state_base::get_name()
{
    return name_;
}

bool state_base::should_pop_char() const
{
	return get_state_type() == state_type::accumulate;
}

std::string state_base::next_state(char c) const
{
    auto it = get_transition(c);
    if (it == transitions_.end())
    {
        return state_err::get_default_name();
    }
    return it->get_target();
}

transition_iter state_base::get_transition(char c) const
{
    return std::find_if(transitions_.begin(), transitions_.end(),
                    [c](auto const& t) {return t.is_usable(c);});
}
