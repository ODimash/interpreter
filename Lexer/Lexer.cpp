#include "Lexer.h"

Lexer::Lexer(std::string& sourceCode) : sourceCode(sourceCode) {
	currentPosition = 0;
};

std::vector<Token> Lexer::tokenize() {
	std::vector<Token> tokens;
	while (!isAtEnd()) {
		tokens.push_back(scanToken());
	}
	return tokens;
}

char Lexer::peek(int relativePosition) {
	int targetPosition = currentPosition + relativePosition;
	if (targetPosition >= sourceCode.size())
		return 0;

	return sourceCode[targetPosition];
}

char Lexer::advance() {
	currentPosition++;
	return peek(-1);
}

bool Lexer::isAtEnd() {
	return currentPosition >= sourceCode.size();
}

bool Lexer::isHexNumber(char c) {
	std::string hexNumbers = "abcdefABCDEF";
	return hexNumbers.find(c) != std::string::npos;
}

Token Lexer::scanToken() {
	char c = advance();
	while (isspace(c)) {
		printf("::::::::::::This is space: %c\n", c);
		c = advance();
	}

	switch (c) {
	case '+': return { TokenType::PLUS, "" };
	case '-': return { TokenType::MINUS, "" };
	case '*': return { TokenType::MULTIPLY, "" };
	case '/': return { TokenType::DIVIDE, "" };
	case '%': return { TokenType::REMAINDER, "" };
	case '(': return { TokenType::LEFT_PAREN, "" };
	case ')': return { TokenType::RIGHT_PAREN, "" };
	case '{': return { TokenType::LEFT_BRACE, "" };
	case '}': return { TokenType::RIGHT_BRACE, "" };
	case ';': return { TokenType::SEMICOLON, "" };

	case '=':
		if (peek(0) == '=') return { TokenType::EQUAL, "" };
		else return { TokenType::ASSIGN, "" };
	case '<':
		if (peek(0) == '=') return { TokenType::LESS_THAN_OR_EQUAL, "" };
		else return { TokenType::LESS_THAN, "" };
	case '>':
		if (peek(0) == '=') return { TokenType::GREATER_THAN_OR_EQUAL, "" };
		else return { TokenType::GREATER_THAN, "" };

	default:
		if (isalpha(c)) return scanWord();
		if (isdigit(c)) return scanNumber();
		break;
	}
	return { TokenType::INVALIDE_TYPE, ""};
}

Token Lexer::scanWord() {
	std::string word;
	word += peek(-1);
	while (isalnum(peek(0))) {
		word += advance();
	}
	return tokenizeWord(word);
}

Token Lexer::scanNumber() {
	char currentChar = peek(-1);
	if (currentChar == '0' && peek(0) == 'x')
		return tokenizeHexNumber();
	else if (currentChar == '0' && peek(0) == 'b')
		return tokenizeBinaryNumber();
	else
		return tokenizeDecNumber();

}

Token Lexer::tokenizeWord(std::string& word) {
	if (word == "if")      return { TokenType::IF, "" };
	if (word == "else")    return { TokenType::ELSE, "" };
	if (word == "loop")    return { TokenType::LOOP, "" };
	if (word == "while")   return { TokenType::WHILE, "" };
	if (word == "for")     return { TokenType::FOR, "" };
	if (word == "return")  return { TokenType::RETURN, "" };
	if (word == "true")    return { TokenType::TRUE, "" };
	if (word == "false")   return { TokenType::FALSE, "" };
	if (word == "None")    return { TokenType::NONE, "" };
	else                   return { TokenType::IDENTIFIER_VAR, word };


}

Token Lexer::tokenizeDecNumber() {
	std::string number;
	char currentChar = peek(-1);
	bool isHaveDot = false;

	while (isdigit(currentChar) || currentChar == '.') {
		if (currentChar == '.') {
			if (!isHaveDot) isHaveDot = true;
			else break;
		}
		number += currentChar;
		currentChar = advance();
	}

	if (isHaveDot) return { TokenType::FLOAT, number };
	else return { TokenType::INT, number };
}

Token Lexer::tokenizeHexNumber() {
	std::string number;
	advance(); // убираем курсор с "х"
	char currentChar = advance();

	while (isdigit(currentChar) || isHexNumber(currentChar)) {
		number += currentChar;
		currentChar = advance();
	}
	return { TokenType::HEX, number };
}

Token Lexer::tokenizeBinaryNumber() {
	std::string number;
	advance(); // убираем курсор с "b"
	char currentChar = advance();

	while (isdigit(currentChar) || isHexNumber(currentChar)) {
		number += currentChar;
		currentChar = advance();
	}
	return { TokenType::BINARY, number };
}
