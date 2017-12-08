#pragma once
#include "state_helper_macro.h"
#include "state_base.h"

class state_default : public state_base
{
    DECLARE_STATE(state_default, state_base)
public:
    state_default() = default;
    ~state_default() = default;

    virtual state_type get_state_type() const override;
    virtual void apply(char c, pending_lexeme& lex) const {};
};

