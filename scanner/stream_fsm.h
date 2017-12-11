#pragma once
#include <iosfwd>
#include "pending_lexeme.h"
#include <map>
#include <memory>
#include <string>
#include "state_base.h"

using state_map = std::map<std::string, std::shared_ptr<state_base>>;

class stream_fsm
{
public:
	stream_fsm() = default;
	~stream_fsm() = default;

    void set_current_state(std::string const& state);
    bool emplace_state(std::shared_ptr<state_base> state);
    bool get_next(std::istream& str, pending_lexeme& pending);

private:
    void generate_unknown_state_ex();

private:
    std::string current_;
    state_map state_map_;
};