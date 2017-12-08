#pragma once
#include <vector>

enum class temp_lex_type
{
	literal,
	id_or_keyword,
	delim
};

class pending_lexeme
{
public:
	pending_lexeme();
	~pending_lexeme();

private:
	std::vector<char> data_;
	bool is_complete_;
	temp_lex_type type_;
};

