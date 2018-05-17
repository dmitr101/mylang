#include "stdafx.h"
#include "generator_facade.h"
#include <stack>
#include "../core/lexeme_traits.h"


std::vector<std::shared_ptr<rpn::symbol>> generator_facade::create_rpn_stream(out_lexeme_table const& lexems)
{
	auto const& table = lexems.get_all();
	std::vector<std::shared_ptr<rpn::symbol>> res;
	res.reserve(table.size());

	std::stack<std::shared_ptr<rpn::operation>> op_stack;
	for (auto lit = table.cbegin() + 3; lit != table.cend(); ++lit)
	{
		auto const& l = *lit;
		if (l->check(identifier()) || l->check(literal()))
		{
			res.push_back(std::make_shared<rpn::operand>(
				(l->check(literal()) ? rpn::operand::operand_type::constant 
									 : rpn::operand::operand_type::variable), 
				l->get_id()));
			continue;
		}
		auto op = rpn::get_operation_map().at(l->get_data());
		if (op.ope_tag_ == rpn::ope_tag::ope_flush)
		{
			continue;
		}
		if (op_stack.empty() || op_stack.top()->priority_ < op.priority_)
		{
			op_stack.push(std::make_shared<rpn::operation>(op));
		}
		else
		{
			while (!op_stack.empty() && (op_stack.top()->priority_ > op.priority_))
			{
				res.push_back(op_stack.top());
				op_stack.pop();
			}
			op_stack.push(std::make_shared<rpn::operation>(op));
		}
	}

	return res;
}