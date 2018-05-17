#pragma once
#include <cstdint>
#include <unordered_map>

namespace rpn
{
	struct symbol
	{
		enum class symbol_type
		{
			operand,
			operation
		};

		symbol(symbol_type type)
			: sym_type_(type) {}

		symbol_type sym_type_;
	};

	struct operand : symbol
	{
		enum class operand_type
		{
			constant,
			variable,
		};

		operand()
			: symbol(symbol_type::operand) {}
		operand(operand_type type, size_t id)
			: symbol(symbol_type::operand)
			, operand_type_(type)
			, id_(id) {}

		operand_type operand_type_;
		size_t		 id_;
	};

	enum class ope_tag
	{
		ope_declaration = 0,
		ope_assignment,
		ope_plus,
		ope_minus,
		ope_mul,
		ope_div,
		ope_lbracket,
		ope_rbracket,

		ope_do,
		ope_while,
		ope_enddo,

		ope_if,
		ope_then,
		ope_endif,

		ope_and,
		ope_or,
		ope_not,

		ope_equals,
		ope_not_equals,
		ope_less,
		ope_greater,
		ope_greater_equals,
		ope_less_equals,

		ope_read,
		ope_write,

		ope_flush,
		ope_jmp,
		ope_jmpc,

		ope_COUNT
	};

	struct operation : symbol
	{
		operation()
			: symbol(symbol_type::operation) {}
		operation(ope_tag tag, size_t priority)
			: symbol(symbol_type::operation)
			, ope_tag_(tag)
			, priority_(priority) {}

		ope_tag ope_tag_;
		size_t	priority_;
	};

	std::unordered_map<std::string, operation> const& get_operation_map();
}
