#pragma once
#include "stream_fsm.h"
#include "../core/out_lexeme_table.h"
class scanner_private
{
    friend class scanner_private_builder;
public:
    scanner_private();
    ~scanner_private() = default;

    void scan(std::istream& input_stream);
    std::unique_ptr<out_lexeme_table>&& get_result();

private:
    void handle_pending_lexeme(pending_lexeme&& lex);
    void handle_pending_err(pending_lexeme&& lex);
    size_t create_id(pending_lexeme const& lex);

private:
    std::unique_ptr<out_lexeme_table> result_;

    std::set<std::string> keywords_;
    stream_fsm fsm_;
    size_t current_line_;
};

