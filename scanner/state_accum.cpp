#include "state_accum.h"

state_type state_accum::get_state_type() const
{
    return state_type::accumulate;
}

void state_accum::apply(char c, pending_lexeme& lex) const
{
    lex.push_char(c);
}
