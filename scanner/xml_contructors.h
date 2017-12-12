#pragma once
#include "scanner_private.h"
#include <memory>
#include <string>

namespace xml_fsm_constructors
{
    std::unique_ptr<scanner_private> create_context(std::string const& config_file_name);
}
namespace xfc = xml_fsm_constructors;