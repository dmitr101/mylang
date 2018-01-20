#include "../scanner/scanner_facade.h"
#include "../scanner/scanner_exception.h"
#include "../parser/parser_facade.h"
#include "../parser/parse_result.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <atlconv.h>
#pragma optimize("", off)
static char const* const SCANNER_DEFAULT_CONFIG_FILENAME = "D:/KPI/3/1/translators/mylang_all/conf/sconfig.xml";

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

void log_parse_result(parse_result const& result, out_lexeme_table const& lexems)
{
	time_t t = time(0);
	tm* now = localtime(&t);
	std::stringstream str;
	str << "D:/KPI/3/1/translators/mylang_all/"
		<< now->tm_year + 1900 << "y" << now->tm_mon + 1 
		<< "m" << now->tm_mday << "d" << now->tm_hour 
		<< "h" << now->tm_min  << "m.plog";
	auto fname = str.str().c_str();
	std::ofstream log;
	log.open(str.str().c_str(), std::ios::out);
	auto const& errs = result.get_errors();
	if (errs.empty())
	{
		log << "PARSE SUCCESS \n";
	}
	else
	{
		log << "PARSE FAILED \n";
	}
	log << "LEXEM TABLE: \n";
	for (auto const& l : lexems.get_all())
	{
		log << l->get_index() << "." << l->get_data() << " : " << l->get_type_as_string() << "; \n";
	}
	log << "ERRORS: \n";
	for (auto const& err : errs)
	{
		log << "On line: " << err.line_ << " In expr: " << err.word_ << " Info: " << err.info_ << '\n';
	}
	log.flush();
	log.close();
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
        log_parse_result(*result, *lexems);
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