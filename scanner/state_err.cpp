#include "state_err.h"

state_type state_err::get_state_type() const
{
    return state_type::error;
}

void state_err::apply(char c, pending_lexeme& lex) const
{
    lex.complete();
    lex.set_type(temp_lex_type::invalid);
}
