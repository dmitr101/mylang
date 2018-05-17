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
		symbol_type sym_type_;

	};

	struct operand : symbol
	{
		enum class type
		{
			constant,
			variable,
		};

		type	operand_type_;
		size_t  id_;
	};

	enum class ope_tag
	{
		ope_assignment = 0,
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

		ope_COUNT
	};

	struct operation : symbol
	{
		operation() = default;
		operation(ope_tag tag, size_t priority)
			: ope_tag_(tag)
			, priority_(priority) {}

		ope_tag ope_tag_;
		size_t	priority_;
	};

	std::unordered_map<std::string, operation> const& get_operation_map();
}
