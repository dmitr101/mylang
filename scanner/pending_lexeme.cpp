#include "pending_lexeme.h"

void pending_lexeme::push_char(char c)
{
    data_.push_back(c);
}

std::string&& pending_lexeme::retrieve_data()
{
    return std::move(data_);
}

std::string const& pending_lexeme::get_data() const
{
    return data_;
}

void pending_lexeme::set_type(temp_lex_type type)
{
    type_ = type;
}

temp_lex_type pending_lexeme::get_type() const
{
    return type_;
}

void pending_lexeme::complete()
{
    is_complete_ = true;
}

bool pending_lexeme::is_complete() const
{
    return is_complete_;
}

bool pending_lexeme::is_valid() const
{
    return type_ == temp_lex_type::invalid;
}
