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
			operation,
			label
		};

		symbol(symbol_type type)
			: sym_type_(type) {}

		symbol_type const sym_type_;
		std::string dbg_sym_;
	};

	struct operand : public symbol
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

		ope_while,
		ope_do,
		ope_enddo,

		ope_if,
		ope_then,
		ope_else,
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

		ope_semicolon,
		ope_jmp,
		ope_jmp_false,

		ope_COUNT
	};

	struct operation : public symbol
	{
		operation()
			: symbol(symbol_type::operation) {}
		operation(ope_tag tag, size_t priority, bool to_final)
			: symbol(symbol_type::operation)
			, ope_tag_(tag)
			, priority_(priority) 
			, to_final_(to_final) {}
		operation& operator=(operation const& oth)
		{
			ope_tag_ = oth.ope_tag_;
			priority_ = oth.priority_;
			to_final_ = oth.to_final_;
			return *this;
		}

		ope_tag ope_tag_;
		size_t	priority_;
		bool	to_final_;
	};

	std::unordered_map<std::string, operation> const& get_operation_map();

	struct label : public symbol
	{
		label()
			: symbol(symbol_type::label) {}
		label(size_t id, size_t symbol_idx)
			: symbol(symbol_type::label)
			, id_(id)
			, symbol_idx_(symbol_idx) {}
		size_t id_;
		size_t symbol_idx_;
	};
}
