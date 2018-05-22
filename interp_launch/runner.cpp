#include "runner.h"
#include "executor_factory.h"
#include "converter.h"


void runner::run(rpn::pstream&& script, out_lexeme_table&& table)
{
	script_ = std::move(script);
	sym_table_ = std::move(table);
	state_.reset();
	executor_factory::get_instance().register_all();
	run_internal();
}

void runner::run_internal()
{
	for (; state_.current() < script_.size(); state_.inc())
	{
		auto sym = script_[state_.current()];
		if (sym->sym_type_ == rpn::symbol::symbol_type::operation)
		{
			auto ope = std::static_pointer_cast<rpn::operation>(sym);
			auto exe = executor_factory::get_instance().create(ope->ope_tag_);
			exe->execute(state_);
		}
		else
		{
			state_.push_stack(rpn_to_multival::convert(sym, sym_table_, state_));
		}
	}
}
