#pragma once
#include "../core/singleton_macro.h"
#include "generator_common.h"
#include <vector>
#include <stack>
#include <memory>
#include "../core/out_lexeme_table.h"
#include "rpn_symbol.h"

namespace rpn
{
	using pstream = std::vector<std::shared_ptr<rpn::symbol>>;
}

struct generation_step
{
	std::string lexem_;
	std::string op_stack_;
	std::string lbl_stack_;
	std::string rpn_;
};

class generator_facade
{
	DECLARE_SINGLETON_DLL(generator_facade, GENERATOR_API)
public:
	GENERATOR_API rpn::pstream create_rpn_stream(out_lexeme_table const& lexems);
	GENERATOR_API void set_generate_steps(bool val) { generate_steps_ = val; }
	GENERATOR_API std::vector<generation_step> const& get_steps() const { return steps_; }

private:
	void flush_intermediate(std::shared_ptr<lexeme> l,
							std::vector<std::shared_ptr<rpn::symbol>> const& res_stream,
							std::stack<std::shared_ptr<rpn::operation>> const& op_stack,
							std::stack<std::shared_ptr<rpn::label>> const& lbl_stack);

private:
	bool generate_steps_ = false;
	std::vector<generation_step> steps_;
};

