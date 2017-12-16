#include "../scanner/scanner_facade.h"
#include "../scanner/scanner_exception.h"
#include "../parser/parser_facade.h"
#include "../parser/parse_result.h"
#include <fstream>
#include <iostream>
#include <atlconv.h>
#pragma optimize("", off)
static char const* const SCANNER_DEFAULT_CONFIG_FILENAME = "conf/sconfig.xml";

void print_arg_count_error()
{
    std::cout << "There must be exactly one arg - source file path!" << std::endl;
}

void print_unknown_error()
{
    std::cout << "Something went wrong, but I don't know what. Sorry." << std::endl;
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

void print_and_free(BSTR msg)
{
    USES_CONVERSION;
    const char *pString = OLE2CA(msg);
    std::cout << pString << std::endl;
    ::SysFreeString(msg);
}

void run_translator(char const* src_file)
{
    try
    {
        auto& scanner = scanner_facade::get_instance();
        scanner.initialize(SCANNER_DEFAULT_CONFIG_FILENAME);
        auto src = load_src(src_file);
        auto lexems = scanner.scan(src);

        auto& parser = parser_facade::get_instance();
        auto result = parser.parse(*lexems);
        log_parse_result(*result);
    }
    catch (scanner_exception* ex)
    {
        print_and_free(ex->msg());
    }
    catch (std::exception* ex)
    {
        std::cout << ex->what() << std::endl;
        print_unknown_error();
    }
}

void main(int argc, char** argv)
{
    if (argc != 2)
    {
        print_arg_count_error();
        return;
    }
    run_translator(*(argv + 1));
    system("pause");
}