#pragma once
#include "../core/singleton_macro.h"
#include "parser_common.h"
#include "parse_result.h"
#include "../core/out_lexeme_table.h"
#include <memory>

class parser_facade
{
	DECLARE_SINGLETON_DLL(parser_facade, PARSER_API)
public:
	PARSER_API std::shared_ptr<parse_result> parse(out_lexeme_table const& table);
};

