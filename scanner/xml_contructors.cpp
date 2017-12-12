#include "xml_contructors.h"
#include "xml_helpers.h"
#include "scanner_exception.h"
#include "char_class.h"
#include <map>
#include <set>
#include "scanner_private_builder.h"
#include "state_factory.h"

namespace
{
    char const* const ROOT_TAG      = "scanner";
    char const* const KEYWORDS_TAG  = "keywords";
    char const* const KEYWORD_TAG   = "keyword";
    char const* const CLASSES_TAG   = "classes";
    char const* const CLASS_TAG     = "class";
    char const* const STATES_TAG    = "states";
    char const* const STATE_TAG     = "state";
                                    
    char const* const NAME_ATTR     = "name";
    char const* const TYPE_ATTR     = "type";
    char const* const CLASS_ATTR    = "class";
    char const* const TARGET_ATTR   = "target";
    char const* const REXP_ATTR     = "rexp";

    char const* const DEFAULT_STATE = "default";
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
        auto& classes = get_first_child(root, CLASSES_TAG);
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
        }, CLASS_TAG);
        return result;
    }

    std::vector<std::string> get_keywords(XMLElement const& root)
    {
        auto& keywords = get_first_child(root, KEYWORDS_TAG);
        std::vector<std::string> result;
        for_each_child_check_name(keywords,
            [&result](auto const& keyword_tag)
        {
            auto keyword = get_attr(keyword_tag, NAME_ATTR);
            result.emplace_back(std::move(keyword));
        }, KEYWORD_TAG);
        return result;
    }

    std::shared_ptr<state_base> create_state(XMLElement const& node, std::map<std::string, char_class> const& classes)
    {
        auto type = get_attr(node, TYPE_ATTR);
        auto result = state_factory::get_instance().create(type);
        result->set_name(get_attr(node, NAME_ATTR));
        for_each_child_check_name(node,
            [&result, &classes](auto const& transition_tag)
        {
            auto transition_class_attr = get_attr(transition_tag, CLASS_ATTR);
            auto transition_target_attr = get_attr(transition_tag, TARGET_ATTR);
            auto transition_class = classes.find(transition_class_attr)->second;
            result->add_transition(transition(transition_class, transition_target_attr));
        }, KEYWORD_TAG);

        return std::shared_ptr<state_base>(result.release());
    }

    stream_fsm create_fsm(XMLElement const& root)
    {
        auto classes = create_classes(root);
        auto& states = get_first_child(root, STATES_TAG);
        std::vector<std::shared_ptr<state_base>> ready_states;
        for_each_child_check_name(states,
            [&ready_states, &classes](auto const& state_tag)
        {
            auto state = create_state(state_tag, classes);
            ready_states.emplace_back(std::move(state));
        }, STATE_TAG);
        stream_fsm result;
        result.set_current_state(DEFAULT_STATE);
        for (auto state : ready_states)
        {
            result.emplace_state(state);
        }
        return std::move(result);
    }
}

namespace xml_fsm_constructors
{


    std::unique_ptr<scanner_private> create_context(std::string const& config_file_name)
    {
        auto doc = load_doc(config_file_name);
        auto& root = get_first_child(*doc, ROOT_TAG);

        scanner_private_builder builder;
        builder.add_keywords(get_keywords(root));
        builder.set_fsm(std::move(create_fsm(root)));

        return builder.get();
    }
}