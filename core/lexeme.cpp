#include "lexeme.h"
#include "lexeme_traits.h"

lexeme_type lexeme::get_type() const
{
    return type_;
}

CORE_API std::string lexeme::get_type_as_string() const
{
	std::string res;
	switch (type_)
	{
	case lexeme_type::delim:
		res = "delim";
		break;
	case lexeme_type::keyword:
		res = "keyword";
		break;
	case lexeme_type::literal:
		res = "literal";
		break;
	case lexeme_type::id:
		res = "id";
		break;
	case lexeme_type::unknown:
		res = "unknown";
		break;
	}
	return res;
}

size_t lexeme::get_index() const
{
    return index_;
}

size_t lexeme::get_id() const
{
    return id_ ;
}

size_t lexeme::get_line() const
{
	return line_;
}

std::string const & lexeme::get_data() const
{
    return data_;
}

bool lexeme::check(lexeme_trait const & trait) const
{
	return trait.check(*this);
}
