#pragma once
#include "core_common.h"
#include <string>
#include "lexeme_type.h"

class lexeme
{
	friend class lexeme_builder;
    friend class out_lexeme_table;
public:
	CORE_API lexeme_type get_type() const;
    CORE_API size_t get_index() const;
    CORE_API size_t get_id() const;
    CORE_API std::string const& get_data() const;

private:
	lexeme() {}
	
private:
	size_t index_ = -1;
	size_t id_ = -1; //used only if type is id
	lexeme_type type_ = lexeme_type::unknown;
	std::string data_;
};

