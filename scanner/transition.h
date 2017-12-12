#pragma once
#include <string>
#include "char_class.h"
class transition
{
public:
    transition(char_class const& cl, std::string const& target_state);
    ~transition();

	bool is_usable(char c) const;
	std::string const& get_target() const;

private:
    char_class class_;
    std::string target_state_;
};

