#include "out_lexeme_table.h"
#include "lexeme_builder.h"



out_lexeme_table::out_lexeme_table(out_lexeme_table&& other)
    : all_(std::move(other.all_))
{}

out_lexeme_table::out_lexeme_table(out_lexeme_table const& other)
    : all_(other.all_)
{}

size_t out_lexeme_table::get_next_index() const
{
    return all_.size();
}

void out_lexeme_table::push_lexeme(std::shared_ptr<lexeme> lex)
{
    all_.push_back(lex);
}

void out_lexeme_table::copy_and_push_lexeme(lexeme const& lex)
{
    all_.push_back(std::make_shared<lexeme>(lex));
}

bool out_lexeme_table::emplace_lexeme(lexeme_builder&& ready_builder)
{
    all_.push_back(ready_builder.get());
    return true;
}

std::vector<std::shared_ptr<lexeme>> const& out_lexeme_table::get_all() const
{
    return all_;
}
