#include "recursive_descender.h"
#include "../core/lexeme_traits.h"
#include <memory>
#pragma optimize("", off)

recursive_descender::recursive_descender(std::vector<std::shared_ptr<lexeme>> const& lexems)
    : lexems_(lexems)
    , current_it_(lexems_.begin())
    , current_(*current_it_)
    , result_(std::make_shared<parse_result>())
{}

std::shared_ptr<parse_result> recursive_descender::parse()
{
    programm();
    return result_;
}

void recursive_descender::next()
{
    current_it_++;
    current_ = *current_it_;
}

bool recursive_descender::expect(lexeme_trait const& trait)
{
    if (!accept(trait))
    {
        error(std::string("Unexpected symbol. Expected ") + trait.name());
        return false;
    }
    return true;
}

bool recursive_descender::accept(lexeme_trait const& trait)
{
    if (current_->check(trait) && current_it_ != (lexems_.end() - 1))
    {
        next();
        return true;
    }
    return false;
}

void recursive_descender::error(std::string const& msg)
{
    result_->emplace_error(parse_error_info{ current_->get_index(), current_->get_data(), msg });
}

void recursive_descender::identifier_list()
{
	do {
		expect(identifier());
	} while (accept(spec_char(',')));
}

void recursive_descender::factor() {
	if (accept(spec_char('('))) {
		expression();
		expect(spec_char(')'));
	}
	else if (accept(identifier()) || accept(literal())) {
		return;
	}
	else {
		error("syntax error");
		next();
	}
}

void recursive_descender::logical_expression()
{
	accept(spec_char('~'));
	logical_term();
	while (accept(keyword("or"))) {
		logical_term();
	}
}

void recursive_descender::conditional()
{
	logical_expression();
	expect(keyword("then"));
	operations_list();
	if (accept(keyword("else"))) {
		operations_list();
	}
	expect(keyword("endif"));
}

void recursive_descender::cycle()
{
	logical_expression();
	expect(keyword("do"));
	operations_list();
	expect(keyword("enddo"));
}

void recursive_descender::assignment()
{
	if (accept(spec_char('='))) {
		expression();
	}
}

void recursive_descender::declaration()
{
	expect(identifier());
	assignment();
}

void recursive_descender::operation()
{
	//TODO: MAKE IF WORK
	if (accept(keyword("read"))) {
		input_output();
	} 
	else if (accept(keyword("write"))) {
		input_output();
	}
	else if(accept(keyword("var"))) {
		declaration();
	}
	else if (accept(identifier())) {
		assignment();
	}
	else if (accept(keyword("while"))) {
		cycle();
	}
	else if (accept(keyword("if"))) {
		conditional();
	}
	else {
		error("Syntax error.");
		next();
	}
}

void recursive_descender::operations_list()
{
	do {
		operation();
	} while (accept(spec_char(';')));
}

void recursive_descender::programm()
{
	if (accept(keyword("module"))) {
		expect(identifier());
		expect(spec_char(';'));
	}
	else {
		error("Missing module declaration!");
	}
	operations_list();
}

void recursive_descender::term()
{
	factor();
	while (accept(spec_char('*')) || accept(spec_char('/'))) {
		factor();
	}
}

void recursive_descender::expression()
{
	accept(spec_char('-'));
	term();
	while (accept(spec_char('+')) || accept(spec_char('-')))
	{
		term();
	}
}

inline void recursive_descender::input_output()
{
	expect(spec_char('('));
	identifier_list();
	expect(spec_char(')'));
}

void recursive_descender::logical_relation()
{
	if (!(accept(spec_char("==")) || accept(spec_char("!=")) || accept(spec_char('>'))
		|| accept(spec_char(">=")) || accept(spec_char('<')) || accept(spec_char("<="))))
		error("syntax error");
}

void recursive_descender::logical_factor()
{
	bool brackets = accept(spec_char('('));
	expression();
	logical_relation();
	expression();
	if (brackets) expect(spec_char(')'));
}

void recursive_descender::logical_term()
{
	logical_factor();
	while (accept(keyword("and"))) {
		logical_factor();
	}
}
