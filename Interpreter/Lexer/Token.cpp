#include <Token.h>

Token::Token(TokenType type, std::string value) : type(type), value(value) {
}

TokenType Token::getType() const {
	return type;
}

std::string Token::getValue() const {
	return value;
}