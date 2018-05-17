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
			res_map["="]		= { ope_tag::ope_assignment,	0 };
			res_map["+"]		= { ope_tag::ope_plus,			0 };
			res_map["-"]		= { ope_tag::ope_minus,			0 };
			res_map["*"]		= { ope_tag::ope_mul,			0 };
			res_map["/"]		= { ope_tag::ope_div,			0 };
			res_map["("]		= { ope_tag::ope_lbracket,		0 };
			res_map[")"]		= { ope_tag::ope_rbracket,		0 };
	
			res_map["do"]		= { ope_tag::ope_do,			0 };
			res_map["while"]	= { ope_tag::ope_while,			0 };
			res_map["enddo"]	= { ope_tag::ope_enddo,			0 };
	
			res_map["if"]		= { ope_tag::ope_if,			0 };
			res_map["then"]		= { ope_tag::ope_then,			0 };
			res_map["endif"]	= { ope_tag::ope_endif,			0 };
	
			res_map["and"]		= { ope_tag::ope_and,			0 };
			res_map["or"]		= { ope_tag::ope_or,			0 };
			res_map["~"]		= { ope_tag::ope_not,			0 };
	
			res_map["=="]		= { ope_tag::ope_equals,		0 };
			res_map["!="]		= { ope_tag::ope_not_equals,	0 };
			res_map["<"]		= { ope_tag::ope_less,			0 };
			res_map[">"]		= { ope_tag::ope_greater,		0 };
			res_map[">="]		= { ope_tag::ope_greater_equals,0 };
			res_map["<="]		= { ope_tag::ope_less_equals,	0 };
	
			
			res_map["read"]		= { ope_tag::ope_read,			0 };
			res_map["write"]	= { ope_tag::ope_write,			0 };
	
			map_inited = true;
		}
		return res_map;
	}
}
