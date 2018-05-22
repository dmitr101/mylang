#include "stdafx.h"
#include "generator_facade.h"
#include "../core/lexeme_traits.h"

namespace
{
	std::shared_ptr<rpn::label> new_label()
	{
		static size_t lbl_gloal_id = 0;
		auto res = std::make_shared<rpn::label>(lbl_gloal_id, 0);
		res->dbg_sym_ = "lbl_" + std::to_string(lbl_gloal_id);
		lbl_gloal_id++;
		return res;
	}
}

rpn::pstream generator_facade::create_rpn_stream(out_lexeme_table const& lexems)
{
	auto const& table = lexems.get_all();
	std::vector<std::shared_ptr<rpn::symbol>> res_stream;
	res_stream.reserve(table.size());

	std::stack<std::shared_ptr<rpn::operation>> op_stack;
	std::stack<std::shared_ptr<rpn::label>> lbl_stack;
	for (auto lit = table.cbegin() + 3; lit != table.cend(); ++lit)
	{
		auto const& l = *lit;
		rpn::operation cur_op;
		if (l->check(identifier()) || l->check(literal()))
		{
			auto data_sym = std::make_shared<rpn::operand>(
				(l->check(literal())
					? rpn::operand::operand_type::constant
					: rpn::operand::operand_type::variable),
				l->get_id());
			data_sym->dbg_sym_ = l->get_data();
			res_stream.push_back(data_sym);
			goto main_loop_end;
		}
		cur_op = rpn::get_operation_map().at(l->get_data());
		cur_op.dbg_sym_ = l->get_data();
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
			goto main_loop_end;
		}
		if (cur_op.ope_tag_ == rpn::ope_tag::ope_lbracket)
		{
			op_stack.push(std::make_shared<rpn::operation>(cur_op));
			goto main_loop_end;
		}
		if (cur_op.ope_tag_ == rpn::ope_tag::ope_endif)
		{
			auto to_end = lbl_stack.top();
			lbl_stack.pop();
			res_stream.push_back(to_end);
			to_end->symbol_idx_ = res_stream.size() - 1;
			goto main_loop_end;
		}
		if (cur_op.ope_tag_ == rpn::ope_tag::ope_else)
		{
			auto to_else = lbl_stack.top();
			lbl_stack.pop();
			auto to_end = new_label();
			lbl_stack.push(to_end);
			res_stream.push_back(to_end);
			res_stream.push_back(std::make_shared<rpn::operation>(rpn::ope_tag::ope_jmp, 0, true));
			res_stream.back()->dbg_sym_ = "jmp";
			res_stream.push_back(to_else);
			to_else->symbol_idx_ = res_stream.size() - 1;
			goto main_loop_end;
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
			res_stream.back()->dbg_sym_ = "jmp";
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
				res_stream.back()->dbg_sym_ = "jmp_false";
			}
			else if (cur_op.ope_tag_ == rpn::ope_tag::ope_do)
			{
				auto to_end = new_label();
				lbl_stack.push(to_end);
				res_stream.push_back(to_end);
				res_stream.push_back(std::make_shared<rpn::operation>(rpn::ope_tag::ope_jmp_false, 0, true));
				res_stream.back()->dbg_sym_ = "jmp_false";
			}
			else
			{
				op_stack.push(std::make_shared<rpn::operation>(cur_op));
			}
		}
	main_loop_end:
		if (generate_steps_)
		{
			flush_intermediate(l, res_stream, op_stack, lbl_stack);
		}
	}
	return res_stream;
}

namespace
{
	//symbol container
	template<typename Cont>
	std::string to_string_list(Cont const& c)
	{
		std::string result;
		result.reserve(c.size() * 2);
		for (auto p : c)
		{
			result += p->dbg_sym_;
			result += ',';
		}
		return result;
	}
}

void generator_facade::flush_intermediate(std::shared_ptr<lexeme> l,
	std::vector<std::shared_ptr<rpn::symbol>> const& res_stream,
	std::stack<std::shared_ptr<rpn::operation>> const& op_stack,
	std::stack<std::shared_ptr<rpn::label>> const& lbl_stack)
{
	generation_step s;
	s.lexem_ = l->get_data();
	s.lbl_stack_ = to_string_list(lbl_stack._Get_container());
	s.op_stack_ = to_string_list(op_stack._Get_container());
	s.rpn_ = to_string_list(res_stream);
	steps_.push_back(s);
}