#pragma once
#include "lexeme.h"
#include <string>
struct lexeme_trait
{
	CORE_API lexeme_trait() = default;
	CORE_API virtual ~lexeme_trait() = default;

	virtual bool check(lexeme const& lex) const = 0;
};

struct keyword : public lexeme_trait
{
	CORE_API explicit keyword(std::string const& word);
	virtual bool check(lexeme const& lex) const override;

	std::string word_;
};

struct identifier : public lexeme_trait
{
	CORE_API explicit identifier() = default;
	virtual bool check(lexeme const& lex) const override;
};

struct literal : public lexeme_trait
{
	CORE_API explicit literal() = default;
	virtual bool check(lexeme const& lex) const override;
};

struct spec_char : public lexeme_trait
{
    CORE_API explicit spec_char(std::string const& val);
    CORE_API explicit spec_char(char val);
	virtual bool check(lexeme const& lex) const override;

	std::string val_;
};