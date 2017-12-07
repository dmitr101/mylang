#include "xml_contructors.h"
#include "../external/tinyxml2/tinyxml2.h"
#include "scanner_exception.h"

using namespace tinyxml2;
namespace
{
    scanner_init_exception* create_doc_parse_ex(XMLDocument const& doc)
    {
        scanner_init_exception* ex = new scanner_init_exception();
        ex->push_err_line("Scanner config parse error!");
        ex->push_err_line("tinyxml2 error info:");
        ex->push_err_line(doc.ErrorStr());
        return ex;
    }

    std::unique_ptr<XMLDocument> load_doc_or_throw(std::string const& file_name)
    {
        auto result = std::make_unique<XMLDocument>();
        if (result->LoadFile(file_name.c_str()) != XML_SUCCESS)
        {
            throw create_doc_parse_ex(*result);
        }
        return result;
    }
}

namespace xml_fsm_constructors
{
    std::unique_ptr<scanner_context> create_context(std::string const& config_file_name)
    {
        auto doc = load_doc_or_throw(config_file_name);
        auto result = std::make_unique<scanner_context>();
        return result;
    }
}