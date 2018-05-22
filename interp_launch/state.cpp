#include "state.h"
#include <algorithm>

void script_state::reset()
{
	stack_.clear();
	variables_.clear();
	current_instruction_ = 0;
}

std::size_t script_state::current() const
{
	return current_instruction_;
}

void script_state::inc()
{
	++current_instruction_;
}

void script_state::jmp(std::size_t target)
{
	current_instruction_ = target;
}

bool script_state::push_variable(std::shared_ptr<var_val> var)
{
	auto id = var->id_;
	auto it = std::find_if(variables_.begin(), variables_.end(), [id](auto v) {return v->id_ == id; });
	if (it == variables_.end())
	{
		variables_.push_back(var);
		return true;
	}
	return false;
}

std::shared_ptr<var_val> script_state::get_var(std::size_t id) const
{
	auto it = std::find_if(variables_.begin(), variables_.end(), [id](auto v) {return v->id_ == id; });
	if (it != variables_.end())
	{
		return *it;
	}
	return nullptr;
}

void script_state::push_stack(std::shared_ptr<multival_base> m)
{
	stack_.push_back(m);
}

std::shared_ptr<multival_base> script_state::pop_stack()
{
	auto res = stack_.back();
	stack_.pop_back();
	return res;
}
