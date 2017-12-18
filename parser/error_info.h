#pragma once
#include "../better-enums/enum.h"

struct parse_error_info
{
    size_t line_;
    std::string word_;
    std::string info_;
};