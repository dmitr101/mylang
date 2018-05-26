#include "lexeme_builder.h"

lexeme_builder::lexeme_builder()
{
    result_.reset(new lexeme());
}

lexeme_builder & lexeme_builder::set_index(size_t index)
{
    result_->index_ = index;
    return *this;
}

lexeme_builder& lexeme_builder::set_id(size_t id)
{
    result_->id_ = id;
    return *this;
}

CORE_API lexeme_builder & lexeme_builder::set_line(size_t line)
{
	result_->line_ = line;
	return *this;
}

lexeme_builder& lexeme_builder::set_type(lexeme_type type)
{
    result_->type_ = type;
    return *this;
}

lexeme_builder& lexeme_builder::set_data(std::string&& data)
{
    result_->data_ = std::move(data);
    return *this;
}

std::shared_ptr<lexeme> lexeme_builder::get()
{
    return result_;
}
