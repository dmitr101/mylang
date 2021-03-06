#pragma once
#include "scanner_common.h"
#include "vcruntime_exception.h"
#include <sstream>
#include <wtypes.h>
class scanner_scan_exception : public std::exception
{
public:
	scanner_scan_exception();
	~scanner_scan_exception();

    SCANNER_API const char* what() const override;
};

class scanner_exception : public std::exception
{
public:
    scanner_exception() = default;
    scanner_exception(char const* ini_err_line);
    ~scanner_exception() = default;
    void push_err_line(char const* line);

    SCANNER_API BSTR msg() const;

private:
    std::stringstream data_;
};