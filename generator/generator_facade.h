#pragma once
#include "../core/singleton_macro.h"
#include "generator_common.h"
#include <vector>
#include <memory>
#include "../core/out_lexeme_table.h"
#include "rpn_symbol.h"

namespace rpn
{
	using pstream = std::vector<std::shared_ptr<rpn::symbol>>;
}

class generator_facade
{
	DECLARE_SINGLETON_DLL(generator_facade, GENERATOR_API)
public:
	GENERATOR_API rpn::pstream create_rpn_stream(out_lexeme_table const& lexems);
};

