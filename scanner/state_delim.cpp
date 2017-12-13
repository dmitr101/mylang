#include "state_delim.h"

state_type state_delim::get_state_type() const
{
    return state_type::result;
}

void state_delim::apply(char c, pending_lexeme& lex) const
{
    lex.complete();
    lex.set_type(temp_lex_type::delim);
}
