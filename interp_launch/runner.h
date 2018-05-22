#pragma once
#include <vector>
#include "state.h"
#include "../generator/generator_facade.h"

class runner
{
public:
	runner() = default;
	~runner() = default;

	void run(rpn::pstream&& script, out_lexeme_table&& table);

private:
	void run_internal();

private:
	script_state state_;
	rpn::pstream script_;
	out_lexeme_table sym_table_;
};

