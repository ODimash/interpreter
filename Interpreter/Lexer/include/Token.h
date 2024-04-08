#pragma once
#include <string>
#include "TokenType.h"

class Token {
public:
	Token(TokenType type, std::wstring value);
	TokenType getType() const;
	std::wstring getValue() const;

private:
	TokenType type;
	std::wstring value;
};