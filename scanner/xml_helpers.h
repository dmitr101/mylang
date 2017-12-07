#pragma once
#include "../external/tinyxml2/tinyxml2.h"
#include <memory>
#include <string>
#include <functional>

namespace xml_helpers
{
    std::unique_ptr<tinyxml2::XMLDocument> load_doc(std::string const& file_name);
    tinyxml2::XMLElement const& get_first_child(tinyxml2::XMLNode const& node, std::string const& name);
    void for_each_child_check_name(tinyxml2::XMLElement const& el, std::function<void(tinyxml2::XMLElement const&)> func, std::string const& child_name);
    std::string get_attr(tinyxml2::XMLElement const& el, std::string const& name);
}