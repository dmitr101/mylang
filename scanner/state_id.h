#pragma once
#include "state_base.h"

class state_id : public state_base
{
    DECLARE_STATE(state_id, state_base)
public:
    state_id() = default;
    ~state_id() = default;

    virtual state_type get_state_type() const override;
    virtual void apply(char c, pending_lexeme& lex) const;
};

