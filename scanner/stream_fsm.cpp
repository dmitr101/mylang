#include "stream_fsm.h"
#include "scanner_exception.h"

void stream_fsm::set_current_state(std::string const& state)
{
    current_ = state;
}

bool stream_fsm::emplace_state(std::shared_ptr<state_base> state)
{
    return state_map_.try_emplace(state->get_name(), state).second;
}

bool stream_fsm::get_next(std::istream& str, pending_lexeme& pending)
{
    do
    {
        auto state_it = state_map_.find(current_);
        if (state_it == state_map_.end())
        {
            generate_unknown_state_ex();
        }
        auto state = state_it->second;
        auto c = state->should_pop_char() ?
                        str.get() : str.peek();
        state->apply(c, pending);
        current_ = state->next_state(c);
        if (pending.is_complete())
        {
            break;
        }
    } while (true);
    return pending.is_valid();
}

void stream_fsm::generate_unknown_state_ex()
{
    auto ex = new scanner_exception();
    ex->push_err_line("Scan error!");
    ex->push_err_line("Unknown state:");
    ex->push_err_line(current_.c_str());
    throw ex;
}
