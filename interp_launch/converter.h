#pragma once
#include <memory>
#include "multivalue.h"
#include "state.h"
#include "../generator/rpn_symbol.h"
#include "../core/out_lexeme_table.h"

namespace rpn_to_multival
{
	std::shared_ptr<multival_base> convert(std::shared_ptr<rpn::symbol> sym, out_lexeme_table const& table, script_state const& state);
}