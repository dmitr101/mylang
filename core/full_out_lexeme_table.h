#pragma once
#include "core_common.h"
#include "lexeme.h"
#include <memory>
#include <vector>
#include <set>

struct CORE_API out_lexeme_table
{
	std::vector<std::shared_ptr<lexeme>> all_;
	std::set<std::weak_ptr<lexeme>> literals_;
	std::set<std::weak_ptr<lexeme>> ids_;
};