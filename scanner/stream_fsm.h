#pragma once
#include <iosfwd>
#include "pending_lexeme.h"
class stream_fsm
{
public:
	stream_fsm();
	~stream_fsm();

    bool get_next(std::istream& str, pending_lexeme& pending);
};