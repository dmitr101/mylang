#pragma once
#include "parser_common.h"
#include "error_info.h"
#include <vector>
#include <memory>
#include "semantic_tree.h"
class parse_result
{
public:
	parse_result();
	PARSER_API ~parse_result() = default;

    void push_error(parse_error_info const& err);
    void emplace_error(parse_error_info&& err);
	PARSER_API std::vector<parse_error_info> const& get_errors() const;

private:
    std::vector<parse_error_info> errors_;
    std::shared_ptr<semantic_tree> stree_;
};

