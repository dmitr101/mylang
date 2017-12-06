#pragma once
#include "../core/singleton_macro.h"
#include "parser_common.h"
#include "parse_result.h"
#include "../core/full_out_lexeme_table.h"
#include <memory>

class parser_facade
{
	DECLARE_SINGLETON(parser_facade)
public:
	std::unique_ptr<parse_result> parse(out_lexeme_table const& table);
};

