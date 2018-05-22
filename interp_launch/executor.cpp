#include "executor.h"
#include <iostream>

namespace
{
	template<typename BOp>
	auto arythmetic(script_state& state, BOp const& op)
	{
		auto f = state.pop_stack();
		auto s = state.pop_stack();
		auto res_val = op(
			std::dynamic_pointer_cast<val_helper<float>>(s)->val_,
			std::dynamic_pointer_cast<val_helper<float>>(f)->val_);
		auto res = std::make_shared<num_val>();
		res->val_ = res_val;
		return res;
	}
	template<typename BOp>
	auto comparisson(script_state& state, BOp const& op)
	{
		auto f = state.pop_stack();
		auto s = state.pop_stack();
		auto res_val = op(
			std::dynamic_pointer_cast<val_helper<float>>(f)->val_,
			std::dynamic_pointer_cast<val_helper<float>>(s)->val_);
		auto res = std::make_shared<bool_val>();
		res->val_ = res_val;
		return res;
	}
	template<typename BOp>
	auto logic(script_state& state, BOp const& op)
	{
		auto f = state.pop_stack();
		auto s = state.pop_stack();
		auto res_val = op(
			f->as<bool_val>()->val_,
			s->as<bool_val>()->val_);
		auto res = std::make_shared<bool_val>();
		res->val_ = res_val;
		return res;
	}
}

namespace execs
{
	void assign::execute(script_state& state)
	{
		auto from_val = state.pop_stack();
		auto fval = from_val->as<num_val>();
		auto to_val = state.pop_stack();
		auto var = to_val->as<var_val>();
		var->val_ = fval->val_;
		state.push_stack(to_val);
	}
	void declare::execute(script_state& state) 
	{
		auto m = state.pop_stack();
		auto v = std::dynamic_pointer_cast<var_val>(m);
		state.push_variable(v);
		state.push_stack(v);
	}
	void plus::execute(script_state& state) 
	{
		state.push_stack(arythmetic(state, [](auto v1, auto v2) {return v1 + v2; }));
	}
	void minus::execute(script_state& state) 
	{
		state.push_stack(arythmetic(state, [](auto v1, auto v2) {return v1 - v2; }));
	}
	void mul::execute(script_state& state)
	{
		state.push_stack(arythmetic(state, [](auto v1, auto v2) {return v1 * v2; }));
	}
	void div::execute(script_state& state)
	{
		state.push_stack(arythmetic(state, [](auto v1, auto v2) {return v1 / v2; }));
	}
	void and::execute(script_state& state)
	{
		state.push_stack(logic(state, [](auto v1, auto v2) {return v1 && v2; }));
	}
	void or::execute(script_state& state)
	{
		state.push_stack(logic(state, [](auto v1, auto v2) {return v1 || v2; }));
	}
	void not::execute(script_state& state)
	{
		auto f = state.pop_stack();
		auto res = std::make_shared<bool_val>();
		res->val_ = !f->as<bool_val>()->val_;
	}
	void equals::execute(script_state& state)
	{
		state.push_stack(comparisson(state, [](auto v1, auto v2) {return v1 == v2; }));
	}
	void not_equals::execute(script_state& state)
	{
		state.push_stack(comparisson(state, [](auto v1, auto v2) {return v1 != v2; }));
	}
	void less::execute(script_state& state)
	{
		state.push_stack(comparisson(state, [](auto v1, auto v2) {return v1 < v2; }));
	}
	void greater::execute(script_state& state)
	{
		state.push_stack(comparisson(state, [](auto v1, auto v2) {return v1 > v2; }));
	}
	void greater_equals::execute(script_state& state)
	{
		state.push_stack(comparisson(state, [](auto v1, auto v2) {return v1 >= v2; }));
	}
	void less_equals::execute(script_state& state)
	{
		state.push_stack(comparisson(state, [](auto v1, auto v2) {return v1 <= v2; }));
	}
	void read::execute(script_state& state)
	{
		auto val = state.pop_stack();
		auto var = val->as<var_val>();
		std::cin >> var->val_;
	}
	void write::execute(script_state& state)
	{
		auto val = state.pop_stack();
		auto var = val->as<var_val>();
		std::cout << var->val_;
	}
	void jmp::execute(script_state& state) 
	{
		auto val = state.pop_stack();
		auto lbl = val->as<label_val>();
		state.jmp(lbl->target_sym_);
	}
	void jmp_false::execute(script_state& state)
	{
		auto lval = state.pop_stack();
		auto lbl = lval->as<label_val>();
		auto eval = state.pop_stack();
		auto val = eval->as<bool_val>();
		if (val->val_)
		{
			state.jmp(lbl->target_sym_);
		}
	}
}