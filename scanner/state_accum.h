#pragma once
#include "state_base.h"
class state_accum : public state_base
{
    DECLARE_STATE(state_accum, state_base)
public:
    state_accum() = default;
    ~state_accum() = default;

    virtual state_type get_state_type() const override;
    virtual void apply(char c, pending_lexeme& lex) const;
};

