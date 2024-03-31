#include <Lexer.h>

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
	return peek(0);
}

char Lexer::advance(int moveAmount) {
	currentPosition += moveAmount;
	return peek(0);
}

bool Lexer::isAtEnd() {
	return currentPosition >= sourceCode.size();
}

bool Lexer::isHexNumber(char c) {
	std::string hexNumbers = "abcdefABCDEF";
	return hexNumbers.find(c) != std::string::npos;
}

Token Lexer::scanToken() {
	char c = peek(0);
	while (isspace(c)) {
		c = advance();
	}

	switch (c) {
	case '+': advance(); return { TokenType::PLUS, "" };
	case '-': advance(); return { TokenType::MINUS, "" };
	case '*': advance(); return { TokenType::MULTIPLY, "" };
	case '/': advance(); return { TokenType::DIVIDE, "" };
	case '%': advance(); return { TokenType::REMAINDER, "" };
	case '(': advance(); return { TokenType::LEFT_PAREN, "" };
	case ')': advance(); return { TokenType::RIGHT_PAREN, "" };
	case '{': advance(); return { TokenType::LEFT_BRACE, "" };
	case '}': advance(); return { TokenType::RIGHT_BRACE, "" };
	case ';': advance(); return { TokenType::SEMICOLON, "" };
	case '=': advance(); return { TokenType::EQUAL, "" };
	case ',': advance(); return { TokenType::COMMA, "" };
	case '#': advance(); return tokenizeComment();
	case '\"': advance(); return tokenizeString();
	case ':': 
		if (peek(1) == '=') {
			advance(2);
			return {TokenType::ASSIGN, ""};
		}
		break;
	case '<':
		if (peek(1) == '=') {
			advance(2);
			return { TokenType::LESS_THAN_OR_EQUAL, "" };
		} else {
			advance();
			return { TokenType::LESS_THAN, "" };
		}
	case '>':
		if (peek(1) == '=') {
			advance(2);
			return { TokenType::GREATER_THAN_OR_EQUAL, "" };
		} else {
			advance();
			return { TokenType::GREATER_THAN, "" };
		}

	default:
		if (isalpha(c)) return scanWord();
		if (isdigit(c)) return scanNumber();
		break;
	}

	std::string invalide_type_info = "\"" + std::string(1, c) + "\": [" + std::to_string(currentPosition) + ']';
	advance();
	return { TokenType::INVALIDE_TYPE, invalide_type_info};
}

Token Lexer::scanWord() {
	std::string word;
	char currentChar = peek(0);
	while (isalnum(currentChar)) {
		word += currentChar;
		currentChar = advance();
	}
	return tokenizeWord(word);
}

Token Lexer::scanNumber() {
	char currentChar = peek(0);
	if (currentChar == '0' && peek(1) == 'x')
		return tokenizeHexNumber();
	else if (currentChar == '0' && peek(1) == 'b')
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
	if (word == "and")     return { TokenType::AND, "" };
	if (word == "or")      return { TokenType::OR, "" };
	if (word == "not")     return { TokenType::NOT, ""};
	if (word == "none")    return { TokenType::NONE, "" };
	if (word == "var")     return { TokenType::VAR, "" };
	if (word == "func")    return { TokenType::FUNC, "" };
	if (word == "msgBox")  return { TokenType::MSGBOX, "" };
	if (word == "inputBox") return { TokenType::MSGBOX, "" };
	else                    return tokenizeIdentifier(word);


}

Token Lexer::tokenizeDecNumber() {
	std::string number;
	char currentChar = peek(0);
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
	while (advance() != 'x'); // убираем курсор с "х"
	char currentChar = advance();

	while (isdigit(currentChar) || isHexNumber(currentChar)) {
		number += currentChar;
		currentChar = advance();
	}
	return { TokenType::HEX, number };
}

Token Lexer::tokenizeBinaryNumber() {
	std::string number;
	while (advance() != 'b'); // убираем курсор с "b"
	char currentChar = advance();

	while (isdigit(currentChar) || isHexNumber(currentChar)) {
		number += currentChar;
		currentChar = advance();
	}
	return { TokenType::BINARY, number };
}


Token Lexer::tokenizeComment() {
	std::string comment;
	char currentChar = peek(0);
	while (currentChar != '\n') {
		comment += currentChar;
		currentChar = advance();
	}
	return { TokenType::COMMENT, comment };
}

Token Lexer::tokenizeIdentifier(std::string& word) {
	char currentChar = peek(0);
	while (isspace(currentChar)) {
		currentChar = advance();
	};
	if (peek(0) == '(') {
		return { TokenType::IDENTIFIER_FUNC, word };
	} 
	return { TokenType::IDENTIFIER_VAR, word };
}

Token Lexer::tokenizeString() {
	std::string str;
	char currentChar = peek(0);
	while (currentChar != '\"') {
		str += currentChar;
		currentChar = advance();
	}
	advance();
	return { TokenType::STRING, str };
}