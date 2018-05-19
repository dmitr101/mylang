#pragma once
#include "core_common.h"
#include "lexeme.h"
#include <memory>
#include <vector>
#include <set>

class out_lexeme_table
{
public:
    out_lexeme_table() = default;
    out_lexeme_table(out_lexeme_table const& other);
    out_lexeme_table(out_lexeme_table&& other);

    CORE_API size_t get_next_index() const;
    CORE_API void push_lexeme(std::shared_ptr<lexeme> lex);
    CORE_API void copy_and_push_lexeme(lexeme const& lex);
    CORE_API bool emplace_lexeme(lexeme_builder&& ready_builder);

	CORE_API std::vector<std::shared_ptr<lexeme>> const& get_all() const;
	CORE_API std::vector<std::shared_ptr<lexeme>> const& get_ids() const;
	CORE_API std::vector<std::shared_ptr<lexeme>> const& get_consts() const;

private:
	void push_internal(std::shared_ptr<lexeme> lex);

private:
	std::vector<std::shared_ptr<lexeme>> all_;
	std::vector<std::shared_ptr<lexeme>> ids_;
	std::vector<std::shared_ptr<lexeme>> consts_;
};