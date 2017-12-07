#include "scanner_facade.h"
#include "xml_contructors.h"

bool scanner_facade::initialize(std::string const& config_file_name)
{
    context_ = xfc::create_context(config_file_name);
    return false;
}

std::unique_ptr<out_lexeme_table> scanner_facade::scan(std::istream & str)
{
    return{ nullptr };
}
