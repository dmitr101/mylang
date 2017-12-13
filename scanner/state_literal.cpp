#include "state_literal.h"

state_type state_literal::get_state_type() const
{
    return state_type::result;
}

void state_literal::apply(char c, pending_lexeme& lex) const
{
    lex.complete();
    lex.set_type(temp_lex_type::literal);
}
