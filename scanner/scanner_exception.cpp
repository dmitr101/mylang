#include "scanner_exception.h"
#pragma optimize("", off)

scanner_scan_exception::scanner_scan_exception()
{
}


scanner_scan_exception::~scanner_scan_exception()
{
}

char const* scanner_scan_exception::what() const
{
    return nullptr;
}

scanner_init_exception::scanner_init_exception(char const* ini_err_line)
{
    push_err_line(ini_err_line);
}

void scanner_init_exception::push_err_line(char const* line)
{
    data_ << line << "\n";
}

const char* scanner_init_exception::what() const
{
    auto s = data_.str();
    auto c = s.c_str();
    return c;
}
