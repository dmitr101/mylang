#include "out_lexeme_table.h"
#include "lexeme_builder.h"
#include "lexeme_traits.h"



out_lexeme_table::out_lexeme_table(out_lexeme_table&& other)
    : all_(std::move(other.all_))
	, ids_(std::move(other.ids_))
	, consts_(std::move(other.consts_))
{}

out_lexeme_table::out_lexeme_table(out_lexeme_table const& other)
    : all_(other.all_)
	, ids_(other.ids_)
	, consts_(other.consts_)
{}

size_t out_lexeme_table::get_next_index() const
{
    return all_.size();
}

void out_lexeme_table::push_lexeme(std::shared_ptr<lexeme> lex)
{
	push_internal(lex);
}

void out_lexeme_table::copy_and_push_lexeme(lexeme const& lex)
{
	push_internal(std::make_shared<lexeme>(lex));
}

bool out_lexeme_table::emplace_lexeme(lexeme_builder&& ready_builder)
{
	push_internal(ready_builder.get());
    return true;
}

void out_lexeme_table::push_internal(std::shared_ptr<lexeme> lex)
{
	all_.push_back(lex);
	if (lex->check(identifier()))
	{
		lex->id_ = ids_.size();
		ids_.push_back(lex);
	}
	else if (lex->check(literal()))
	{
		lex->id_ = consts_.size();
		consts_.push_back(lex);
	}
}

std::vector<std::shared_ptr<lexeme>> const& out_lexeme_table::get_all() const
{
    return all_;
}

std::vector<std::shared_ptr<lexeme>> const& out_lexeme_table::get_ids() const
{
	return ids_;
}
std::vector<std::shared_ptr<lexeme>> const& out_lexeme_table::get_consts() const
{
    return consts_;
}