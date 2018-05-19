#include "stdafx.h"
#include "generator_facade.h"
#include <stack>
#include "../core/lexeme_traits.h"

namespace
{
	std::shared_ptr<rpn::label> new_label()
	{
		static size_t lbl_gloal_id = 0;
		auto res = std::make_shared<rpn::label>(lbl_gloal_id, 0);
		lbl_gloal_id++;
		return res;
	}
}

std::vector<std::shared_ptr<rpn::symbol>> generator_facade::create_rpn_stream(out_lexeme_table const& lexems)
{
	auto const& table = lexems.get_all();
	std::vector<std::shared_ptr<rpn::symbol>> res_stream;
	res_stream.reserve(table.size());

	std::stack<std::shared_ptr<rpn::operation>> op_stack;
	std::stack<std::shared_ptr<rpn::label>> lbl_stack;
	size_t cur_comma_count = -1;
	for (auto lit = table.cbegin() + 3; lit != table.cend(); ++lit)
	{
		auto const& l = *lit;
		if (l->check(identifier()) || l->check(literal()))
		{
			res_stream.push_back(std::make_shared<rpn::operand>(
				(l->check(literal()) 
					? rpn::operand::operand_type::constant
					: rpn::operand::operand_type::variable),
				l->get_id()));
			continue;
		}
		auto cur_op = rpn::get_operation_map().at(l->get_data());
		if (cur_op.ope_tag_ == rpn::ope_tag::ope_semicolon)
		{
			while (!op_stack.empty())
			{
				auto to_push = op_stack.top();
				op_stack.pop();
				if (to_push->to_final_)
				{
					res_stream.push_back(to_push);
				}
			}
			continue;
		}
		if (cur_op.ope_tag_ == rpn::ope_tag::ope_endif)
		{
			auto to_end = lbl_stack.top();
			lbl_stack.pop();
			res_stream.push_back(to_end);
			to_end->symbol_idx_ = res_stream.size() - 1;
			continue;
		}
		if (cur_op.ope_tag_ == rpn::ope_tag::ope_else)
		{
			auto to_else = lbl_stack.top();
			lbl_stack.pop();
			auto to_end = new_label();
			lbl_stack.push(to_end);
			res_stream.push_back(to_end);
			res_stream.push_back(std::make_shared<rpn::operation>(rpn::ope_tag::ope_jmp, 0, true));
			res_stream.push_back(to_else);
			to_else->symbol_idx_ = res_stream.size() - 1;
			continue;
		}
		if (cur_op.ope_tag_ == rpn::ope_tag::ope_while)
		{
			auto to_loop = new_label();
			lbl_stack.push(to_loop);
			res_stream.push_back(to_loop);
			to_loop->symbol_idx_ = res_stream.size() - 1;
		}
		if (cur_op.ope_tag_ == rpn::ope_tag::ope_enddo)
		{
			auto to_end = lbl_stack.top();
			lbl_stack.pop();
			auto to_loop = lbl_stack.top();
			lbl_stack.pop();
			res_stream.push_back(to_loop);
			res_stream.push_back(std::make_shared<rpn::operation>(rpn::ope_tag::ope_jmp, 0, true));
			res_stream.push_back(to_end);
			to_end->symbol_idx_ = res_stream.size() - 1;
		}
		if (op_stack.empty() || op_stack.top()->priority_ < cur_op.priority_)
		{
			op_stack.push(std::make_shared<rpn::operation>(cur_op));
		}
		else
		{
			while (!op_stack.empty() && (op_stack.top()->priority_ >= cur_op.priority_))
			{
				auto cur_out_op = op_stack.top();
				op_stack.pop();
				if (cur_out_op->to_final_)
				{
					res_stream.push_back(cur_out_op);
				}
			}
			if (cur_op.ope_tag_ == rpn::ope_tag::ope_then)
			{
				auto to_else = new_label();
				lbl_stack.push(to_else);
				res_stream.push_back(to_else);
				res_stream.push_back(std::make_shared<rpn::operation>(rpn::ope_tag::ope_jmp_false, 0, true));
			}
			else if (cur_op.ope_tag_ == rpn::ope_tag::ope_do)
			{
				auto to_end = new_label();
				lbl_stack.push(to_end);
				res_stream.push_back(to_end);
				res_stream.push_back(std::make_shared<rpn::operation>(rpn::ope_tag::ope_jmp_false, 0, true));
			}
			else
			{
				op_stack.push(std::make_shared<rpn::operation>(cur_op));
			}
		}
	}
	return res_stream;
}