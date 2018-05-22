#pragma once
#include <set>
#include <memory>
#include <vector>
#include "multivalue.h"

class script_state
{
public:
	void reset();

	std::size_t current() const;
	void inc();
	void jmp(std::size_t target);

	bool push_variable(std::shared_ptr<var_val> var);
	std::shared_ptr<var_val> get_var(std::size_t id) const;
	void push_stack(std::shared_ptr<multival_base> m);
	std::shared_ptr<multival_base> pop_stack();

private:
	std::vector<std::shared_ptr<multival_base>> stack_;
	std::vector<std::shared_ptr<var_val>> variables_;
	std::size_t current_instruction_;
};

