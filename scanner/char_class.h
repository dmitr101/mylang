#pragma once
#include <regex>
#include <string>

class char_class
{
public:
    char_class() = default;
    char_class(std::string const& name, std::regex const& rexp);
    char_class(std::string&& name, std::regex&& rexp);
    ~char_class() = default;

    std::string const& get_name() const;
    bool belongs(char c) const;

private:
    std::string name_;
    std::regex  rexp_;
};

