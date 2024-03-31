#pragma once

#include <string>
#include <vector>
#include "TokenTypes.h"

struct Token {
	TokenType type;
	std::string text;
};

class Lexer {
public:
	Lexer(std::string& sourceCode);
	std::vector<Token> tokenize();

private:
	std::string sourceCode;
	std::size_t currentPosition;

	char peek(int relativePosition);
	char advance();
	char advance(int moveAmount);

	Token scanToken();
	Token scanWord();
	Token scanNumber();

	Token tokenizeWord(std::string& word);
	Token tokenizeDecNumber();
	Token tokenizeHexNumber();
	Token tokenizeBinaryNumber();

	bool isAtEnd();
	bool isHexNumber(char c);

};