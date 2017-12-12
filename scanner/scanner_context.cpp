#include "scanner_context.h"
#include "state_accum.h"
#include "state_default.h"
#include "state_err.h"
#include "state_factory.h"
#include "../core/lexeme_builder.h"

namespace
{
    void register_states()
    {
        auto& factory = state_factory::get_instance();
        factory.register_state<state_accum>();
        factory.register_state<state_default>();
        factory.register_state<state_err>();
    }

    lexeme_type convert(temp_lex_type t)
    {
        return lexeme_type::unknown;
    }
}

scanner_context::scanner_context()
{
    register_states();
    result_ = std::make_unique<out_lexeme_table>();
}

void scanner_context::scan(std::istream& input_stream)
{
    while (!input_stream.eof())
    {
        pending_lexeme lex;
        if (!fsm_.get_next(input_stream, lex))
        {
            handle_pending_err(std::move(lex));
            return;
        }
        handle_pending_lexeme(std::move(lex));
    }
}

std::unique_ptr<out_lexeme_table>&& scanner_context::get_result()
{
    return std::move(result_);
}

void scanner_context::handle_pending_lexeme(pending_lexeme&& lex)
{
    auto builder = lexeme_builder()
        .set_index(result_->get_next_index())
        .set_id(create_id(lex))
        .set_type(convert(lex.get_type()))
        .set_data(std::move(lex.get_data()));
    result_->emplace_lexeme(std::move(builder));
}

void scanner_context::handle_pending_err(pending_lexeme&& lex)
{

}

size_t scanner_context::create_id(pending_lexeme const& lex)
{
    return 0;
}
