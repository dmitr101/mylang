#pragma once
#include <string>

enum class multival_type
{
	numeric,
	boolean,
	id,
	label
};

struct multival_base
{
	virtual multival_type get_type() const = 0;
	template<typename T>
	T* as()
	{
		static_assert(std::is_base_of<multival_base, T>::value, "For multivals only.");
		return get_type() == T::get_stype() ? static_cast<T*>(this) : nullptr;
	}
};

template<multival_type mt>
struct multival_template : multival_base
{
	static multival_type get_stype() { return mt; }
	virtual multival_type get_type() const override { return mt; }
};

template<typename T>
struct val_helper
{
	T val_;
};

struct num_val : multival_template<multival_type::numeric>, val_helper<float>
{
};

struct var_val : multival_template<multival_type::id>, val_helper<float>
{
	size_t id_;
	std::string name_;
};

struct bool_val : multival_template<multival_type::boolean>, val_helper<bool>
{
};

struct label_val : multival_template<multival_type::label>
{
	std::size_t target_sym_;
};