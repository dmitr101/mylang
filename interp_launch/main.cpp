#include "../scanner/scanner_facade.h"
#include "../scanner/scanner_exception.h"
#include "../parser/parser_facade.h"
#include "../parser/parse_result.h"
#include "../generator/generator_facade.h"
#include "runner.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <atlconv.h>

#include "argh.h"

static char const* const SCANNER_DEFAULT_CONFIG_FILENAME = "sconfig.xml";

std::string own_path() 
{
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	auto pos = std::string(buffer).find_last_of("\\/");
	return std::string(buffer).substr(0, pos);
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

void print_help()
{
	std::cout <<
R"(
Usage: angsli <-help> <-src=YOUR_SOURCE_FILE_PATH> <-ltable> <-rpn> <-rgen>
-help (or no params) : print this message
-src : specify a script, without it all latter options don't make sense
-ltable : generate file YOUR_SOURCE_FILE_PATH.ltable with tables of lexems and ids
-rpn : generate file YOUR_SOURCE_FILE_PATH.rpn with rpn representation of the code
-rgen : generate file YOUR_SOURCE_FILE_PATH.rgen with step by step showed rpn generation process
-run : run the script
)" 
	<< std::endl;
}

void print_no_file()
{
	std::cout <<
R"(
There is no such source file.
)"
<< std::endl;
}

void print_with_spaces(std::ofstream& log, std::string const& str, size_t overall_size)
{
	for (size_t i = 0; i < overall_size; ++i)
	{
		log << ((i < str.size()) ? str[i] : ' ');
	}
	log << '|';
}

void print_ltable_file(std::string const& src_path, out_lexeme_table const& lexems)
{
	std::ofstream log;
	log.open((src_path + ".ltable"), std::ios::out | std::ios::trunc);
	std::size_t col_size = 10;

	log << "ALL :\n";
	print_with_spaces(log, "Text", col_size);
	print_with_spaces(log, "Index", col_size);
	print_with_spaces(log, "Line", col_size);
	log << '\n';
	for (auto const& l : lexems.get_all())
	{
		print_with_spaces(log, l->get_data(), col_size);
		print_with_spaces(log, std::to_string(l->get_index()), col_size);
		print_with_spaces(log, std::to_string(l->get_line()), col_size);
		log << '\n';
	}

	log << "IDS :\n";
	print_with_spaces(log, "Name", col_size);
	print_with_spaces(log, "Index", col_size);
	log << '\n';
	for (auto const& l : lexems.get_ids())
	{
		print_with_spaces(log, l->get_data(), col_size);
		print_with_spaces(log, std::to_string(l->get_id()), col_size);
		log << '\n';
	}

	log << "CONSTS :\n";
	print_with_spaces(log, "Val", col_size);
	print_with_spaces(log, "Index", col_size);
	log << '\n';
	for (auto const& l : lexems.get_consts())
	{
		print_with_spaces(log, l->get_data(), col_size);
		print_with_spaces(log, std::to_string(l->get_id()), col_size);
		log << '\n';
	}
}

void print_parse_err(parse_result const& result)
{
	std::cout << "Parsing errors occurred! \n";
	for (auto const& err : result.get_errors())
	{
		std::cout << "On line: " << err.line_ << " In expr: " << err.word_ << " Info: " << err.info_ << '\n';
	}
}

void print_rpn_file(std::string const& src_path, rpn::pstream const& polis)
{
	std::ofstream log;
	log.open((src_path + ".rpn"), std::ios::out | std::ios::trunc);
	for (auto const& rs : polis)
	{
		switch (rs->sym_type_)
		{
		case rpn::symbol::symbol_type::operand:
		case rpn::symbol::symbol_type::operation:
		{
			auto rso = std::static_pointer_cast<rpn::operation>(rs);
			log << " [ " << rso->dbg_sym_ << " ] ";
		}
		break;
		case rpn::symbol::symbol_type::label:
		{
			auto rso = std::static_pointer_cast<rpn::label>(rs);
			log << " [ " << "lbl_" << (int)rso->id_ << " ] ";
		}
		break;
		}
	}
	log << "\n";
}

void print_rgen_file(std::string const& src_path, std::vector<generation_step> const& steps)
{
	std::ofstream log;
	log.open((src_path + ".rgen"), std::ios::out | std::ios::trunc);

	auto max_lex_sz = std::max_element(steps.begin(), steps.end(), 
		[](auto const& s1, auto const& s2) {return s1.lexem_.size() < s2.lexem_.size(); }
	)->lexem_.size() + 5;

	auto max_ost_sz = std::max_element(steps.begin(), steps.end(),
		[](auto const& s1, auto const& s2) {return s1.op_stack_.size() < s2.op_stack_.size(); }
	)->op_stack_.size() + 5;

	auto max_lst_sz = std::max_element(steps.begin(), steps.end(),
		[](auto const& s1, auto const& s2) {return s1.lbl_stack_.size() < s2.lbl_stack_.size(); }
	)->lbl_stack_.size() + 5;

	auto max_rpn_sz = std::max_element(steps.begin(), steps.end(),
		[](auto const& s1, auto const& s2) {return s1.rpn_.size() < s2.rpn_.size(); }
	)->rpn_.size() + 5;

	print_with_spaces(log, "Lex", max_lex_sz);
	print_with_spaces(log, "Ops", max_ost_sz);
	print_with_spaces(log, "Lbls", max_lst_sz);
	print_with_spaces(log, "RPN", max_rpn_sz);
	log << '\n';
	for (auto const& rs : steps)
	{
		print_with_spaces(log, rs.lexem_, max_lex_sz);
		print_with_spaces(log, rs.op_stack_, max_ost_sz);
		print_with_spaces(log, rs.lbl_stack_, max_lst_sz);
		print_with_spaces(log, rs.rpn_, max_rpn_sz);
		log << '\n';
	}
	log << "\n";
}

void main(int argc, char** argv)
{
	argh::parser cmdl;
	cmdl.add_param("src");
	cmdl.parse(argc, argv, argh::parser::NO_SPLIT_ON_EQUALSIGN | argh::parser::PREFER_PARAM_FOR_UNREG_OPTION);
	if (cmdl.size() == 0 || cmdl[{"-help"}])
	{
		print_help();
		return;
	}

	auto src_path = cmdl("-src").str();
	auto src = load_src(src_path.c_str());
	if (!src.good())
	{
		std::cout << "SOURCE: " << src_path << '\n';
		print_no_file();
		return;
	}

	auto& scanner = scanner_facade::get_instance();
	scanner.initialize(own_path() + "\\" + SCANNER_DEFAULT_CONFIG_FILENAME);
	auto lexems = scanner.scan(src);
	if (cmdl[{"-ltable"}])
	{
		print_ltable_file(src_path, *lexems);
	}

	auto& parser = parser_facade::get_instance();
	auto result = parser.parse(*lexems);
	if (!result->all_good())
	{
		print_parse_err(*result);
		return;
	}

	auto& generator = generator_facade::get_instance();
	auto rgen = cmdl[{"-rgen"}];
	generator.set_generate_steps(rgen);
	auto polis = generator.create_rpn_stream(*lexems);
	if (cmdl[{"-rpn"}])
	{
		print_rpn_file(src_path, polis);
	}
	if (rgen)
	{
		print_rgen_file(src_path, generator.get_steps());
	}

	if (cmdl[{"-run"}])
	{
		runner r{};
		auto tbl_ptr = lexems.release();
		r.run(std::move(polis), std::move(*tbl_ptr));
	}
}