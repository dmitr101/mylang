#include "xml_contructors.h"
#include "xml_helpers.h"
#include "scanner_exception.h"
#include "char_class.h"
#include <map>

namespace
{
    char const* const ROOT_NODE = "scanner";
    char const* const CLASSES_NODE = "classes";
    char const* const CLASS_NODE = "class";
    char const* const NAME_ATTR = "name";
    char const* const REXP_ATTR = "rexp";
}

using namespace xml_helpers;
using namespace tinyxml2;
namespace
{
    char_class create_class(XMLElement const& node)
    {
        std::string name_str = get_attr(node, NAME_ATTR);
        std::string rexp_str = get_attr(node, REXP_ATTR);
        std::regex rexp(rexp_str);
        return{ name_str, rexp };
    }

    scanner_exception* create_repeating_classes_ex(std::string const& class_name, size_t line)
    {
        scanner_exception* ex = new scanner_exception();
        ex->push_err_line("Scanner config parse error!");
        ex->push_err_line("Repeating class name: ");
        ex->push_err_line(class_name.c_str());
        ex->push_err_line("Line:");
        ex->push_err_line(std::to_string(line).c_str());
        return ex;
    }

    std::map<std::string, char_class> create_classes(XMLElement const& root)
    {
        auto& classes = get_first_child(root, CLASSES_NODE);
        std::map<std::string, char_class> result;
        for_each_child_check_name(classes, 
        [&result](auto const& class_node)
        {
            auto cl = create_class(class_node);
            auto emp_res = result.try_emplace(cl.get_name(), cl);
            if (!emp_res.second)
            {
                throw create_repeating_classes_ex(cl.get_name(), class_node.GetLineNum());
            }
        }, CLASS_NODE);
        return result;
    }
}

namespace xml_fsm_constructors
{
    std::unique_ptr<scanner_context> create_context(std::string const& config_file_name)
    {
        auto doc = load_doc(config_file_name);
        auto& root = get_first_child(*doc, ROOT_NODE);
        auto classes = create_classes(root);

        auto result = std::make_unique<scanner_context>();
        return result;
    }
}