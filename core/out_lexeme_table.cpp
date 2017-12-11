#include "out_lexeme_table.h"



size_t out_lexeme_table::get_next_index() const
{
    return all_.size();
}

void out_lexeme_table::push_lexeme(std::shared_ptr<lexeme> lex)
{

}

void out_lexeme_table::copy_and_push_lexeme(lexeme const& lex)
{

}

bool out_lexeme_table::emplace_lexeme(lexeme_builder&& ready_builder)
{
    return false;
}
