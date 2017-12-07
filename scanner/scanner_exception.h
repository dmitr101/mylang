#pragma once
#include "scanner_common.h"
#include "vcruntime_exception.h"
#include <sstream>
class scanner_scan_exception : public std::exception
{
public:
	scanner_scan_exception();
	~scanner_scan_exception();

    SCANNER_API const char* what() const override;
};

class scanner_init_exception : public std::exception
{
public:
    scanner_init_exception() = default;
    scanner_init_exception(char const* ini_err_line);
    ~scanner_init_exception() = default;
    void push_err_line(char const* line);

    SCANNER_API const char* what() const override;

private:
    std::stringstream data_;
};