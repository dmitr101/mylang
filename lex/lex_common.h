#pragma once

#ifdef LEX_EXPORTS
#define LEX_API __declspec(dllexport)
#else
#define LEX_API __declspec(dllimport)
#endif


