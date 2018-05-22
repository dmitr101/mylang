#pragma once
#include "../core/singleton_macro.h"
#include <memory>
#include <unordered_map>
#include "executor.h"

class executor_factory
{
	DECLARE_SINGLETON_DEFAULT(executor_factory);
public:
	using product = std::shared_ptr<executor_base>;
	using create_func = product(*)(void);
	template<typename T>
	void register_executor()
	{
		static_assert(std::is_base_of<executor_base, T>::value, "This factory is for executors only!");
		creators_.try_emplace(T::get_ope_tag(), &T::create);
	}
	void register_all();
	product create(rpn::ope_tag tag);

public:
	
	std::unordered_map<rpn::ope_tag, create_func> creators_;
};

