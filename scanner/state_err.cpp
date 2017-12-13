#include "state_err.h"

namespace
{
    char const* const DEFAULT_ERROR_NAME = "error";
}

state_type state_err::get_state_type() const
{
    return state_type::error;
}

void state_err::apply(char c, pending_lexeme& lex) const
{
    lex.complete();
    lex.set_type(temp_lex_type::invalid);
}

std::string state_err::get_default_name()
{
    return DEFAULT_ERROR_NAME;
}
