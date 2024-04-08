#include <Token.h>

Token::Token(TokenType type, std::wstring value) : type(type), value(value) {
}

TokenType Token::getType() const {
	return type;
}

std::wstring Token::getValue() const {
	return value;
}