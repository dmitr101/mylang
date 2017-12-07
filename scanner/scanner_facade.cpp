#include "scanner_facade.h"


bool scanner_facade::initialize(std::ifstream&& config)
{
    return false;
}

std::unique_ptr<out_lexeme_table> scanner_facade::scan(std::istream & str)
{
    return{ nullptr };
}
