#pragma once
#include <vector>

enum class temp_lex_type
{
	literal,
	id_or_keyword,
	delim,
    invalid
};

class pending_lexeme
{
public:
	pending_lexeme() = default;
	~pending_lexeme() = default;

    void push_char(char c);
    std::string&& retrieve_data();
    std::string const& get_data() const;
    void set_type(temp_lex_type type);
    temp_lex_type get_type() const;
    void complete();
    bool is_complete() const;
    bool is_valid() const;

private:
	std::string data_;
	bool is_complete_ = false;
	temp_lex_type type_ = temp_lex_type::delim;
};

