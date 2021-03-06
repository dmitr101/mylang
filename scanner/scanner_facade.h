#pragma once
#include "scanner_common.h"
#include "scanner_private.h"
#include "../core/singleton_macro.h"
#include "../core/out_lexeme_table.h"
#include <memory>
#include <istream>

class scanner_facade
{
	DECLARE_SINGLETON_DLL(scanner_facade, SCANNER_API)
public:
	SCANNER_API bool initialize(std::string const& config_file_name);
    SCANNER_API std::unique_ptr<out_lexeme_table> scan(std::istream& str);

private:
	std::unique_ptr<scanner_private> context_;
};

