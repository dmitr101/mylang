#pragma once
#include <vector>
#include <memory>
#include "../core/lexeme.h"
#include <set>
#include "parse_result.h"

class recursive_descender
{
	recursive_descender(std::vector<std::shared_ptr<lexeme>> const& lexems);
	~recursive_descender() = default;
	std::shared_ptr<parse_result> parse();

private:
	void next();
	bool expect(lexeme_trait const& trait);
	bool accept(lexeme_trait const& trait);
	void error(std::string const& msg);

	void identifier_list();
	void factor();
	void term();
	void expression();
	void input_output();
	void logical_relation();
	void logical_factor();
	void logical_term();
	void logical_expression();
	void conditional();
	void cycle();
	void assignment();
	void declaration();
	void operation();
	void operations_list();
	void programm();

private:
	std::vector<std::shared_ptr<lexeme>> lexems_;
	decltype(lexems_)::iterator current_it_;
	std::shared_ptr<lexeme> current_;
	std::set<std::string> declared_vars_;

	std::shared_ptr<parse_result> result_;
};