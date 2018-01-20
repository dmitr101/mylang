#include "parse_result.h"



parse_result::parse_result()
{
}

void parse_result::push_error(parse_error_info const & err)
{
    errors_.push_back(err);
}

void parse_result::emplace_error(parse_error_info&& err)
{
    errors_.push_back(std::move(err));
}

std::vector<parse_error_info> const & parse_result::get_errors() const
{
	return errors_;
}
