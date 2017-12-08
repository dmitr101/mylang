#pragma once
#include "stream_fsm.h"
#include "../core/out_lexeme_table.h"
class scanner_context
{
public:
	scanner_context();
	~scanner_context();

private:
	out_lexeme_table out_table_;
	bool is_out_table_ready_;
	std::set<std::string> keywords_;
	std::unique_ptr<std::istream> char_stream_;
	stream_fsm fsm_;
	size_t current_line_;
};

