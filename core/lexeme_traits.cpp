#include "lexeme_traits.h"

keyword::keyword(std::string const & word)
	: word_(word)
{}

bool keyword::check(lexeme const & lex) const
{
	return lex.get_type() == lexeme_type::keyword
		&& lex.get_data() == word_;
}

bool identifier::check(lexeme const & lex) const
{
	return lex.get_type() == lexeme_type::id;
}

bool literal::check(lexeme const & lex) const
{
	return lex.get_type() == lexeme_type::literal;
}

spec_char::spec_char(std::string const& val)
	: val_(val)
{}

spec_char::spec_char(char val)
{
    val_.push_back(val);
}

bool spec_char::check(lexeme const & lex) const
{
	return lex.get_type() == lexeme_type::delim
		&& lex.get_data() == val_;
}
