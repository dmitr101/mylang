#pragma once
#include "scanner_common.h"
#include "scanner_context.h"
#include "../core/singleton_macro.h"
#include "../core/out_lexeme_table.h"
#include <memory>
#include <istream>

class scanner_facade
{
	DECLARE_SINGLETON_DLL(scanner_facade, SCANNER_API)
public:
	SCANNER_API bool initialize(std::ifstream&& config);
    SCANNER_API std::unique_ptr<out_lexeme_table> scan(std::istream& str);

private:
	std::vector<std::unique_ptr<scanner_context>> contexts_;
	decltype(contexts_)::iterator current_context_;
};

