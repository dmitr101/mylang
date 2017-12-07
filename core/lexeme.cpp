#include "lexeme.h"

lexeme_type lexeme::get_type() const
{
    return type_;
}

size_t lexeme::get_index() const
{
    return index_;
}

size_t lexeme::get_id() const
{
    return id_ ;
}

std::string const & lexeme::get_data() const
{
    return data_;
}
