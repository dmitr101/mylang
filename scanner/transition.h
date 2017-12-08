#pragma once
#include <string>
class transition
{
public:
    transition();
    ~transition();

	bool is_usable() const;
	std::string const& get_target();

private:

};

