#include "../scanner/scanner_facade.h"
#include "../scanner/scanner_exception.h"
#include "../parser/parser_facade.h"
#include "../parser/parse_result.h"
#include <fstream>
#include <iostream>

void print_arg_count_error()
{

}

void print_help()
{

}

inline std::ifstream get_default_scanner_config()
{
    std::ifstream config;
    config.open("sconfig.xml");
    return config;
}

void print_scanner_config_error()
{

}

void print_scanner_error(char const* txt)
{

}

void print_unknown_error()
{

}

inline std::ifstream load_src(char const* path)
{
    std::ifstream config;
    config.open(path);
    return config;
}

void log_parse_result(parse_result const& result)
{

}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		print_arg_count_error();
		print_help();
		return -1;
	}
	auto& scanner = scanner_facade::get_instance();
	auto config = get_default_scanner_config();
	if (!scanner.initialize(std::move(config)))
	{
		print_scanner_config_error();
		return -1;
	}
	auto file = load_src(*(argv + 1));

	try
	{
		auto lexems = scanner.scan(file);
		auto& parser = parser_facade::get_instance();
		auto result = parser.parse(*lexems);
		log_parse_result(*result);
	}
	catch (scanner_exception ex)
	{
		print_scanner_error(ex.what());
		return -1;
	}
	catch (...)
	{
		print_unknown_error();
		return -1;
	}
	return 0;
}