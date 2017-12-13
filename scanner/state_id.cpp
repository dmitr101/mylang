#include "state_id.h"

state_type state_id::get_state_type() const
{
    return state_type::result;
}

void state_id::apply(char c, pending_lexeme& lex) const
{
    lex.complete();
    lex.set_type(temp_lex_type::id_or_keyword);
}
