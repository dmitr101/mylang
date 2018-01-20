#include "parser_facade.h"
#include "recursive_descender.h"

std::shared_ptr<parse_result> parser_facade::parse(out_lexeme_table const& table)
{
	recursive_descender rd{ table.get_all() };
	return rd.parse();
}
