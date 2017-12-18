#pragma once
#include <vector>
#include <memory>
#include "../core/lexeme.h"
#include "parse_result.h"

class recursive_descender
{
    recursive_descender(std::vector<std::shared_ptr<lexeme>> const& lexems);
    ~recursive_descender() = default;
    std::shared_ptr<parse_result> parse();

private:
    void next();
    void expect(std::string const& word);
    void accept(std::string const& word);
    void try_skip();

    void identifier();
    void identifier_list();
    void literal();
    void factor();
    void term();
    void expression();
    void output();
    void input();
    void logical_factor();
    void logical_term();
    void logical_expression();
    void conditional();
    void cycle();
    void assignment();
    void declaration();
    void operation();
    void operations_list();
    void programm();

private:
    std::vector<std::shared_ptr<lexeme>> lexems_;
    decltype(lexems_)::iterator current_it_;
    std::shared_ptr<lexeme> current_;

    std::shared_ptr<parse_result> result_;
};