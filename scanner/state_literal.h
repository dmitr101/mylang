#pragma once
#include "state_base.h"
class state_literal :
    public state_base
{
    DECLARE_STATE(state_literal, state_base)
public:
    state_literal() = default;
    ~state_literal() = default;

    virtual state_type get_state_type() const override;
    virtual void apply(char c, pending_lexeme& lex) const;
};

