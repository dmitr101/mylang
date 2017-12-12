#pragma once
#include "../core/singleton_macro.h"
#include <memory>
#include "state_base.h"
#include <map>

class state_factory
{
    DECLARE_SINGLETON_DEFAULT(state_factory)
public:
    template<typename T>
    bool register_state()
    {
        static_assert(std::is_base_of<state_base, T>::value, "This factory is for char states only!");
        return creators_.try_emplace(T::get_xml_tag(), &T::create).second;
    }

    template<typename T>
    std::unique_ptr<state_base> create()
    {
        static_assert(std::is_base_of<state_base, T>::value, "This factory is for char states only!");
        return create(T::get_xml_tag());
    }

    std::unique_ptr<state_base> create(std::string const& state_tag)
    {
        auto creator_it = creators_.find(state_tag);
        if (creator_it != creators_.end())
        {
            return creator_it->second();
        }
        return{};
    }

private:
    using create_func = std::unique_ptr<state_base>(*)(void);
    std::map<std::string, create_func> creators_;
};

