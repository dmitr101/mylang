#include "scanner_private.h"
#include "state_accum.h"
#include "state_default.h"
#include "state_err.h"
#include "state_factory.h"
#include "../core/lexeme_builder.h"
#include "state_delim.h"
#include "state_literal.h"
#include "state_id.h"

#pragma optimize("", off)

namespace
{
    void register_states()
    {
        auto& factory = state_factory::get_instance();
        factory.register_state<state_accum>();
        factory.register_state<state_default>();
        factory.register_state<state_err>();
        factory.register_state<state_delim>();
        factory.register_state<state_literal>();
        factory.register_state<state_id>();
    }
}

scanner_private::scanner_private()
    : current_line_(0)
{
    register_states();
    result_ = std::make_unique<out_lexeme_table>();
}

void scanner_private::scan(std::istream& input_stream)
{
    while (!input_stream.eof())
    {
        remove_leading_spaces(input_stream);
        retrieve_next_lexeme(input_stream);
        switch_line(input_stream);
    }
}

std::unique_ptr<out_lexeme_table> scanner_private::get_result()
{
    return std::move(result_);
}

void scanner_private::handle_pending_lexeme(pending_lexeme&& lex)
{
	auto builder = lexeme_builder()
		.set_index(result_->get_next_index())
		.set_id(create_id(lex))
		.set_line(current_line_ + 1)
        .set_type(get_type(lex))
        .set_data(std::move(lex.retrieve_data()));
    result_->emplace_lexeme(std::move(builder));
}

void scanner_private::handle_pending_err(pending_lexeme const& lex)
{
}

void scanner_private::switch_line(std::istream& input_stream)
{
    if (input_stream.peek() == '\n')
    {
        input_stream.get();
        current_line_++;
    }
}

size_t scanner_private::create_id(pending_lexeme const& lex)
{
    return 0;
}

void scanner_private::retrieve_next_lexeme(std::istream& input_stream)
{
    pending_lexeme lex;
    if (!fsm_.get_next(input_stream, lex))
    {
        handle_pending_err(lex);
        return;
    }
    handle_pending_lexeme(std::move(lex));
}

void scanner_private::remove_leading_spaces(std::istream& input_stream)
{
    while (input_stream.peek() == ' ' || input_stream.peek() == '\t' || input_stream.peek() == '\n')
    {
		if (input_stream.peek() == '\n')
		{
			current_line_++;
		}
        input_stream.get();
    }
}

lexeme_type scanner_private::get_type(pending_lexeme const& lex)
{
    lexeme_type result = lexeme_type::unknown;
    switch (lex.get_type())
    {
    case temp_lex_type::delim:
        result = lexeme_type::delim;
        break;
    case temp_lex_type::id_or_keyword:
        result = keywords_.find(lex.get_data()) != keywords_.end() ?
            lexeme_type::keyword : lexeme_type::id;
        break;
    case temp_lex_type::literal:
        result = lexeme_type::literal;
        break;
    default:
        result = lexeme_type::unknown;
        handle_pending_err(lex);
    }
    return result;
}
