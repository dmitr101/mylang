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

void recursive_descender::programm()
{

}
