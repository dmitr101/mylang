#include "xml_helpers.h"
#include "scanner_exception.h"

using namespace tinyxml2;
scanner_init_exception* create_doc_parse_ex(XMLDocument const& doc)
{
    scanner_init_exception* ex = new scanner_init_exception();
    ex->push_err_line("Scanner config parse error!");
    ex->push_err_line("tinyxml2 error info:");
    ex->push_err_line(doc.ErrorStr());
    return ex;
}

scanner_init_exception* create_el_find_ex(std::string const& name)
{
    scanner_init_exception* ex = new scanner_init_exception();
    ex->push_err_line("Scanner config parse error!");
    ex->push_err_line("Couldn't find such element:");
    ex->push_err_line(name.c_str());
    return ex;
}

scanner_init_exception* create_attr_find_ex(XMLElement const& el, std::string const& attr_name)
{
    scanner_init_exception* ex = new scanner_init_exception();
    ex->push_err_line("Scanner config parse error!");
    ex->push_err_line("Couldn't find attribute:");
    ex->push_err_line(attr_name.c_str());
    ex->push_err_line("In element:");
    ex->push_err_line(el.Name());
    ex->push_err_line("On line:");
    ex->push_err_line(std::to_string(el.GetLineNum()).c_str());
    return ex;
}

scanner_init_exception* create_wrong_child_ex(XMLElement const& parent, XMLElement const& child, std::string const& expected)
{
    scanner_init_exception* ex = new scanner_init_exception();
    ex->push_err_line("Scanner config parse error!");
    ex->push_err_line("Unacceptable child:");
    ex->push_err_line(child.Name());
    ex->push_err_line("Line:");
    ex->push_err_line(std::to_string(child.GetLineNum()).c_str());
    ex->push_err_line("In parent:");
    ex->push_err_line(parent.Name());
    ex->push_err_line("Line:");
    ex->push_err_line(std::to_string(parent.GetLineNum()).c_str());
    ex->push_err_line("Expected child:");
    ex->push_err_line(expected.c_str());
    return ex;
}

std::unique_ptr<tinyxml2::XMLDocument> xml_helpers::load_doc(std::string const& file_name)
{
    auto result = std::make_unique<XMLDocument>();
    if (result->LoadFile(file_name.c_str()) != XML_SUCCESS)
    {
        throw create_doc_parse_ex(*result);
    }
    return result;
}

XMLElement const& xml_helpers::get_first_child(XMLNode const& node, std::string const& name)
{
    auto result = node.FirstChildElement(name.c_str());
    if (!result)
    {
        throw create_el_find_ex(name);
    }
    return *result;
}

void xml_helpers::for_each_child_check_name(tinyxml2::XMLElement const& el, std::function<void(tinyxml2::XMLElement const&)> func, std::string const& child_name)
{
    for (auto child = el.FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
    {
        if (!child_name.empty() && child_name != el.Name())
        {
            throw create_wrong_child_ex(el, *child, child_name);
        }
        func(*child);
    }
}

std::string xml_helpers::get_attr(XMLElement const& el, std::string const& name)
{
    auto res = el.Attribute(name.c_str());
    if (!res)
    {
        throw create_attr_find_ex(el, name);
    }
    return{ res };
}
