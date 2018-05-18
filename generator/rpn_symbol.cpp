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

			res_map["var"]		= { ope_tag::ope_declaration,	6 };
			res_map["="]		= { ope_tag::ope_assignment,	6 };

			res_map["+"]		= { ope_tag::ope_plus,			11 };
			res_map["-"]		= { ope_tag::ope_minus,			11 };
			res_map["*"]		= { ope_tag::ope_mul,			12 };
			res_map["/"]		= { ope_tag::ope_div,			12 };
			res_map["("]		= { ope_tag::ope_lbracket,		6 };
			res_map[")"]		= { ope_tag::ope_rbracket,		7 };
	
			res_map["do"]		= { ope_tag::ope_do,			0 };
			res_map["while"]	= { ope_tag::ope_while,			0 };
			res_map["enddo"]	= { ope_tag::ope_enddo,			0 };
	
			res_map["if"]		= { ope_tag::ope_if,			2 };
			res_map["then"]		= { ope_tag::ope_then,			3 };
			res_map["else"]		= { ope_tag::ope_else,			3 };
			res_map["endif"]	= { ope_tag::ope_endif,			0 };
	
			res_map["or"]		= { ope_tag::ope_or,			7 };
			res_map["and"]		= { ope_tag::ope_and,			8 };
			res_map["~"]		= { ope_tag::ope_not,			9 };
	
			res_map["=="]		= { ope_tag::ope_equals,		10 };
			res_map["!="]		= { ope_tag::ope_not_equals,	10 };
			res_map["<"]		= { ope_tag::ope_less,			10 };
			res_map[">"]		= { ope_tag::ope_greater,		10 };
			res_map[">="]		= { ope_tag::ope_greater_equals,10 };
			res_map["<="]		= { ope_tag::ope_less_equals,	10 };
		
			res_map["read"]		= { ope_tag::ope_read,			0 };
			res_map["write"]	= { ope_tag::ope_write,			0 };

			res_map[";"]		= { ope_tag::ope_flush,			0 };
	
			map_inited = true;
		}
		return res_map;
	}
}
