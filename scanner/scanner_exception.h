#pragma once
#include "scanner_common.h"
#include "vcruntime_exception.h"
class scanner_exception : public std::exception
{
public:
	scanner_exception();
	~scanner_exception();

    SCANNER_API const char* what() const override;
};

