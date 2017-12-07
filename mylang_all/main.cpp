#include "../scanner/scanner_facade.h"
#include "../scanner/scanner_exception.h"
#include "../parser/parser_facade.h"
#include "../parser/parse_result.h"
#include <fstream>
#include <iostream>

static char const* const SCANNER_DEFAULT_CONFIG_FILENAME = "sconfig.xml";

void print_arg_count_error()
{

}

void print_help()
{

}

void print_scanner_config_error()
{

}

void print_error(char const* txt)
{

}

void print_unknown_error()
{

}

inline std::ifstream load_src(char const* path)
{
    std::ifstream src;
    src.open(path);
    return src;
}

void log_parse_result(parse_result const& result)
{

}

void run_translator(char const* src_file)
{
    try
    {
        auto file = load_src(src_file);
        auto& scanner = scanner_facade::get_instance();
        scanner.initialize(SCANNER_DEFAULT_CONFIG_FILENAME);
        auto lexems = scanner.scan(file);

        auto& parser = parser_facade::get_instance();
        auto result = parser.parse(*lexems);
        log_parse_result(*result);
    }
    catch (scanner_init_exception* ex)
    {
        print_error(ex->what());
    }
    catch (scanner_scan_exception* ex)
    {
        print_error(ex->what());
    }
    catch (...)
    {
        print_unknown_error();
    }
}

void main(int argc, char** argv)
{
	if (argc != 2)
	{
		print_arg_count_error();
		print_help();
	}
    run_translator(*(argv + 1));
}