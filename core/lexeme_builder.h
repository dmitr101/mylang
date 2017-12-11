#pragma once
#include "core_common.h"
#include "lexeme_type.h"
#include "lexeme.h"
#include <memory>
#include <string>
class lexeme_builder
{
public:
	CORE_API lexeme_builder();
    CORE_API ~lexeme_builder() = default;
    
    CORE_API lexeme_builder& set_index(size_t index);
    CORE_API lexeme_builder& set_id(size_t id);
    CORE_API lexeme_builder& set_type(lexeme_type type);
    CORE_API lexeme_builder& set_data(std::string&& data);
    CORE_API std::shared_ptr<lexeme> get();

private:
    std::shared_ptr<lexeme> result_;
};

