#include "converter.h"

namespace rpn_to_multival
{
	std::shared_ptr<multival_base> convert_operand(std::shared_ptr<rpn::operand> op, out_lexeme_table const& table, script_state const& state)
	{
		if (op->operand_type_ == rpn::operand::operand_type::variable)
		{
			auto res = state.get_var(op->id_);
			if (res)
			{
				return res;
			}
			res = std::make_shared<var_val>();
			res->id_ = op->id_;
			res->name_ = table.get_ids()[op->id_]->get_data();
			res->val_ = 0.f;
			return res;
		}
		else
		{
			auto res = std::make_shared<num_val>();
			res->val_ = std::atof(table.get_consts()[op->id_]->get_data().c_str());
			return res;
		}
	}

	std::shared_ptr<multival_base> convert_label(std::shared_ptr<rpn::label> lbl, out_lexeme_table const& table)
	{
		auto res = std::make_shared<label_val>();
		res->target_sym_ = lbl->symbol_idx_;
		return res;
	}

	std::shared_ptr<multival_base> convert(std::shared_ptr<rpn::symbol> sym, out_lexeme_table const& table, script_state const& state)
	{
		switch (sym->sym_type_)
		{
		case rpn::symbol::symbol_type::operand:
			return convert_operand(std::static_pointer_cast<rpn::operand>(sym), table, state);
		case rpn::symbol::symbol_type::label:
			return convert_label(std::static_pointer_cast<rpn::label>(sym), table);
		default:
			return nullptr;
		}
	}
}