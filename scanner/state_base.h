#pragma once
#include "pending_lexeme.h"
#include "transition.h"
#include "state_helper_macro.h"

using transition_vector = std::vector<transition>;
using transition_iter = transition_vector::const_iterator;

enum class state_type
{
	default,
	accumulate,
	result,
	error
};

class state_base
{
public:
    state_base() = default;
    virtual ~state_base() = default;

	void add_transition(transition const& trans);
    void set_name(std::string const& name);
    std::string const& get_name();
    void set_resulting_state(std::string const& name);
    std::string const& get_resulting_state();

    virtual state_type get_state_type() const = 0;
    virtual bool should_pop_char() const;
	virtual void apply(char c, pending_lexeme& lex) const = 0;
    std::string  next_state(char c) const;

protected:
	transition_iter get_transition(char c) const;

protected:
    std::string name_;
    std::string resulting_state_;
	transition_vector transitions_;
};

