#pragma once
#include <string>
#include <TokenType.h>

class Token {
public:
	Token(TokenType type, std::string value);
	TokenType getType() const;
	std::string getValue() const;

private:
	TokenType type;
	std::string value;
};