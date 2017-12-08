#include "char_state.h"



char_state_base::char_state_base()
{
}


char_state_base::~char_state_base()
{
}

bool char_state_base::should_pop_char() const
{
	return get_state_type() == state_type::accumulate;
}
