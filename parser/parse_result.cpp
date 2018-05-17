#include "parse_result.h"

void parse_result::push_error(parse_error_info const & err)
{
    errors_.push_back(err);
}

void parse_result::emplace_error(parse_error_info&& err)
{
    errors_.push_back(std::move(err));
}

bool parse_result::all_good() const
{
	return errors_.empty();
}

std::vector<parse_error_info> const & parse_result::get_errors() const
{
	return errors_;
}
