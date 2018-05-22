#include "out_lexeme_table.h"
#include "lexeme_builder.h"
#include "lexeme_traits.h"
#include <algorithm>

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

out_lexeme_table& out_lexeme_table::operator=(out_lexeme_table const& other)
{
	all_ = other.all_;
	ids_ = other.ids_;
	consts_ = other.consts_;
	return *this;
}

out_lexeme_table& out_lexeme_table::operator=(out_lexeme_table&& other)
{
	all_ = std::move(other.all_);
	ids_ = std::move(other.ids_);
	consts_ = std::move(other.consts_);
	return *this;
}

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

void out_lexeme_table::push_unique_indexed(std::vector<std::shared_ptr<lexeme>>& vec, std::shared_ptr<lexeme> lex)
{
	auto it = std::find_if(vec.begin(), vec.end(), [lex](auto l) { return lex->get_data() == l->get_data(); });
	if (it == vec.end())
	{
		lex->id_ = vec.size();
		vec.push_back(lex);
	}
	else
	{
		lex->id_ = (*it)->id_;
	}
}

void out_lexeme_table::push_internal(std::shared_ptr<lexeme> lex)
{
	all_.push_back(lex);
	if (lex->check(identifier()))
	{
		push_unique_indexed(ids_, lex);
	}
	else if (lex->check(literal()))
	{
		push_unique_indexed(consts_, lex);
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