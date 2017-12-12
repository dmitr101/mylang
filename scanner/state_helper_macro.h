#pragma once
#include <memory>
#include <string>
#define DECLARE_STATE(classname, baseclass)                     \
    public:                                             \
        static std::unique_ptr<baseclass> create()      \
        {                                               \
            return std::make_unique<classname>();       \
        }                                               \
        static std::string get_xml_tag()                \
        {                                               \
            return #classname;                          \
        }                                               
