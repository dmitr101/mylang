#pragma once
#include <string>
#include "lexeme_type.h"

class lexeme
{
	friend class lexeme_builder;
public:
	lexeme_type get_type() const;
	size_t get_index() const;
	size_t get_id() const;
	std::string const& get_data() const;

private:
	lexeme() {}
	
private:
	size_t index_ = -1;
	size_t id_ = -1; //used only if type is id
	lexeme_type type_ = lexeme_type::unknown;
	std::string data_;
};

