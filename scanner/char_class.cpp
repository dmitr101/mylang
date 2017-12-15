#include "char_class.h"
#pragma optimize("", off)

char_class::char_class(std::string const& name, std::regex const& rexp)
    : name_(name), rexp_(rexp) {}

char_class::char_class(std::string&& name, std::regex&& rexp)
    : name_(std::move(name)), rexp_(std::move(rexp)) {}

std::string const & char_class::get_name() const
{
    return name_;
}

bool char_class::belongs(char c) const
{
    char str[2] = " "; str[0] = c;
    return std::regex_match(str, rexp_);
}
