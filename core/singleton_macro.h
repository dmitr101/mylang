#pragma once
#include "core_common.h"
//singleton declaration macros.
//it uses Meyers singleton as a base 
//it's very simple and convinient and comes threadsafe without any locks to write.


#define FORBID_CONSTRUCTORS(classname)				          \
	private:										          \
		classname() = default;						          \
		classname(classname const& other) = delete;			  \
		classname(classname&& other) = delete;				  \
		classname& operator=(classname&& other) = delete;	  \
		classname& operator=(classname const& other) = delete;

#define CREATE_ACCESSOR(classname, DLL_API)    \
	public:							   \
		DLL_API static classname& get_instance() {	   \
			static classname instance; \
			return instance;		   \
		}							   


#define DECLARE_SINGLETON_DLL(classname, DLL) \
	FORBID_CONSTRUCTORS(classname)	 \
	CREATE_ACCESSOR(classname, DLL)

#define DECLARE_SINGLETON_DEFAULT(classname, DLL) \
	DECLARE_SINGLETON_DLL(classname, )