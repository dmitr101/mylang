#pragma once
#include "pending_lexeme.h"
#include "transition.h"

using transition_vector = std::vector<transition>;
using transition_iter = transition_vector::iterator;

enum class state_type
{
	default,
	accumulate,
	result,
	error
};

class char_state_base
{
public:
    char_state_base();
    ~char_state_base();

	void add_transition(transition const& trans);

	virtual state_type get_state_type() const = 0;
	virtual bool should_pop_char() const;

	virtual void on_enter() {}
	virtual std::string const& apply(char c, pending_lexeme& lex) const = 0;

protected:
	transition_iter get_transition(char c) const;

protected:
	transition_vector transitions_;
};

