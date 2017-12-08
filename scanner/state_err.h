#pragma once
#include "state_base.h"
class state_err :
    public state_base
{
    DECLARE_STATE(state_err, state_base)
public:
    state_err() = default;
    ~state_err() = default;

    virtual state_type get_state_type() const override;
    virtual void apply(char c, pending_lexeme& lex) const;
};

