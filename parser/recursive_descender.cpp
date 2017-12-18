#include "recursive_descender.h"
#include <memory>

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

void recursive_descender::skip_op()
{

}

void recursive_descender::skip(size_t num)
{

}

bool recursive_descender::expect(std::string const& word)
{
    if (!accept(word))
    {
        error("unexpected symbol");
        return false;
    }
    return true;
}

bool recursive_descender::accept(std::string const& word)
{
    if (current_->get_data() == word)
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

void recursive_descender::programm()
{
    if (accept("module"))
    {
        identifier();

    }
    
}
