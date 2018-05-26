#pragma once
#include "core_common.h"
#include <string>
#include "lexeme_type.h"

struct lexeme_trait;
class lexeme
{
	friend class lexeme_builder;
    friend class out_lexeme_table;
public:
	CORE_API lexeme_type get_type() const;
	CORE_API std::string get_type_as_string() const;
    CORE_API size_t get_index() const;
	CORE_API size_t get_id() const;
	CORE_API size_t get_line() const;
    CORE_API std::string const& get_data() const;

	CORE_API bool check(lexeme_trait const& trait) const;

private:
	lexeme() {}
	
private:
	size_t index_ = -1;
	size_t id_ = -1; //used only if type is id
	size_t line_ = 0;
	lexeme_type type_ = lexeme_type::unknown;
	std::string data_;
};

