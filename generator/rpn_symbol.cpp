#include "stdafx.h"
#include "rpn_symbol.h"

namespace rpn
{
	std::unordered_map<std::string, operation> const & get_operation_map()
	{
		static bool map_inited = false;
		static std::unordered_map<std::string, operation> res_map;
		if (!map_inited)
		{
			res_map.reserve((size_t)ope_tag::ope_COUNT);

			res_map["var"]		= { ope_tag::ope_declaration,	7, true };
			res_map["="]		= { ope_tag::ope_assignment,	7, true };

			res_map["+"]		= { ope_tag::ope_plus,			12, true };
			res_map["-"]		= { ope_tag::ope_minus,			12, true };
			res_map["*"]		= { ope_tag::ope_mul,			13, true };
			res_map["/"]		= { ope_tag::ope_div,			13, true };
			res_map["("]		= { ope_tag::ope_lbracket,		7, false };
			res_map[")"]		= { ope_tag::ope_rbracket,		8, false };
																  
			res_map["while"]	= { ope_tag::ope_while,			3, false };
			res_map["do"]		= { ope_tag::ope_do,			3, false };
			res_map["enddo"]	= { ope_tag::ope_enddo,			3, false };
																 
			res_map["if"]		= { ope_tag::ope_if,			3, false };
			res_map["then"]		= { ope_tag::ope_then,			3, false };
			res_map["else"]		= { ope_tag::ope_else,			3, false };
			res_map["endif"]	= { ope_tag::ope_endif,			3, false };
																
			res_map["or"]		= { ope_tag::ope_or,			8, true };
			res_map["and"]		= { ope_tag::ope_and,			9, true };
			res_map["~"]		= { ope_tag::ope_not,			10, true };
	
			res_map["=="]		= { ope_tag::ope_equals,		11, true };
			res_map["!="]		= { ope_tag::ope_not_equals,	11, true };
			res_map["<"]		= { ope_tag::ope_less,			11, true };
			res_map[">"]		= { ope_tag::ope_greater,		11, true };
			res_map[">="]		= { ope_tag::ope_greater_equals,11, true };
			res_map["<="]		= { ope_tag::ope_less_equals,	11, true };
		
			res_map["read"]		= { ope_tag::ope_read,			4, true };
			res_map["write"]	= { ope_tag::ope_write,			4, true };

			res_map[";"]		= { ope_tag::ope_semicolon,		2, false };
	
			map_inited = true;
		}
		return res_map;
	}
}
