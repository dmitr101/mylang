#pragma once
#include "scanner_common.h"
#include "vcruntime_exception.h"
class SCANNER_API scanner_exception :
	public std::exception
{
public:
	scanner_exception();
	~scanner_exception();
};

