#include <Lexer.h>
#include <iostream>
Lexer::Lexer(std::ifstream& sourceFile) : sourceFile(sourceFile), currentLineIndex(0) {
}

TokenVector Lexer::tokenize() {
	std::string lineOfCode;
	while (std::getline(sourceFile, lineOfCode)) {
		currentLineIndex++;
		setNewLine(lineOfCode);
		if (currentLine.peek() == EOF) continue;
		tokenizeLine();
		tokens.push_back({ TokenType::EndLine, "" });
	}

	return tokens;
}

void Lexer::setNewLine(std::string& newLine) {
	currentLine.str(newLine);
	currentLine.clear(); // Сброс флагов ошибок и EOF
	currentLine.seekg(0); // Перемещение позиции чтения в начало строки
}

void Lexer::tokenizeLine() {
	while (currentLine >> currentChar) {
		if (isdigit(currentChar)) tokenizeNumber();
		else if (iscsym(currentChar)) tokenizeWord();
		else if (currentChar == '#') return;
		else tokenizeOperator();
	}
}

void Lexer::tokenizeNumber() {
	if (currentChar == '0') {
		currentChar = currentLine.get();
		switch (currentChar) {
		case('x'): return tokenizeHexNumber();
		case('b'): return tokenizeBinNumber();
		}
	}
	tokenizeDecNumber();
}

void Lexer::tokenizeDecNumber() {
	std::string buffer;
	bool isHaveDot = false;
	while (isdigit(currentChar) || currentChar == '.') {
		buffer += currentChar;
		currentChar = currentLine.get();
		if (currentChar == '.') {
			if (!isHaveDot) isHaveDot = true;
			else return;
		}
	}
	if (isalpha(currentChar)) tokens.push_back({ TokenType::Invalid, getCurrentPosition() }); // Надо написать новый обработчик ошибок для слитых токенов
	else tokens.push_back({ TokenType::ValueNumber, buffer });
	currentLine.unget();
}

void Lexer::tokenizeHexNumber() {
	std::string buffer;
	currentChar = currentLine.get(); // Пропускаем символ "х"
	while (isxdigit(currentChar)) {
		buffer += currentChar;
		currentChar = currentLine.get();
	}
	if (isalpha(currentChar)) tokens.push_back({ TokenType::Invalid, getCurrentPosition() });
	else tokens.push_back({ TokenType::ValueHexNumber, buffer });
	currentLine.unget();
}

void Lexer::tokenizeBinNumber() {
	std::string buffer;
	currentChar = currentLine.get(); // Пропускаем символ "b"
	while (currentChar == '0' or currentChar == '1') {
		buffer += currentChar;
		currentChar = currentLine.get();
	}
	if (isalpha(currentChar) or isdigit(currentChar)) tokens.push_back({ TokenType::Invalid, getCurrentPosition() });
	else tokens.push_back({ TokenType::ValueHexNumber, buffer });
	currentLine.unget();
}

std::string Lexer::getCurrentPosition() {
	return currentLineIndex + ":" + currentLine.tellg();
}

void Lexer::tokenizeOperator() {
	switch (currentChar) {
	case '+': return tokens.push_back({ TokenType::Addition, "" });
	case '-': return tokens.push_back({ TokenType::Subtraction, "" });
	case '*': return tokens.push_back({ TokenType::Multiplication, "" });
	case '/': return tokens.push_back({ TokenType::Division, "" });
	case '%': return tokens.push_back({ TokenType::Modulus, "" });
	case '(': return tokens.push_back({ TokenType::OpenParen, "" });
	case ')': return tokens.push_back({ TokenType::CloseParen, "" });
	case '{': return tokens.push_back({ TokenType::OpenBrace, "" });
	case '}': return tokens.push_back({ TokenType::CloseBrace, "" });
	case '[': return tokens.push_back({ TokenType::OpenBracket, "" });
	case ']': return tokens.push_back({ TokenType::CloseBracket, "" });
	case '@': return tokens.push_back({ TokenType::Insert, "" });
	case '=': return tokens.push_back({ TokenType::Equal, "" });
	case ',': return tokens.push_back({ TokenType::Comma, "" });
	case '"': return tokenizeString();
	case '<':
		if (currentLine.get() == '=') return tokens.push_back({ TokenType::LessThanOrEqual, "" });
		currentLine.unget();
		return tokens.push_back({ TokenType::LessThan, "" });
	case '>':
		if (currentLine.get() == '=') return tokens.push_back({ TokenType::GreaterThanOrEqual, "" });
		currentLine.unget();
		return tokens.push_back({ TokenType::GreaterThan, "" });
	case ':':
		if (currentLine.get() == '=') return tokens.push_back({ TokenType::Assign, "" });
		currentLine.unget();
		return tokens.push_back({ TokenType::Colon, "" });

	default:
		tokens.push_back({ TokenType::Invalid, getCurrentPosition() });
	}
}

void Lexer::tokenizeString() {
	std::string buffer;
	currentChar = currentLine.get(); // пропускаем открывающий '"'
	while (currentChar != '"' and currentChar != EOF) {
		if (currentChar == '\\') {
			handleEscapeChar(buffer);
			continue;
		}
		buffer += currentChar;
		currentChar = currentLine.get();
	}
	currentLine.ignore(1); // пропускаем закрывающий знак '"'
}

void Lexer::handleEscapeChar(std::string& buffer) {
	const std::string escapeChars = "\"\'\n\t\r\b\a";
	currentChar = currentLine.get();
	char result = escapeChars.find(currentChar);
	if (result != std::string::npos) {
		buffer += escapeChars[result];
	} else buffer += currentChar;
}

void Lexer::tokenizeWord() {
	std::string buffer;
	while (iscsym(currentChar)) {
		buffer += currentChar;
		currentChar = currentLine.get();
	}
	tokens.push_back(lookUpWordToken(buffer));
	currentLine.unget();
}

Token Lexer::lookUpWordToken(std::string& word) {
	const std::unordered_map<std::string, Token> keywords = {
		{"if", {TokenType::KeywordIf, ""}},
		{"elif", {TokenType::KeywordElif, ""}},
		{"else", {TokenType::KeywordElse, ""}},
		{"while", {TokenType::KeywordWhile, ""}},
		{"loop", {TokenType::KeywordLoop, ""}},
		{"stop", {TokenType::KeywordStop, ""}},
		{"skip", {TokenType::KeywordSkip, ""}},
		{"fnc", {TokenType::KeywordFnc, ""}},
		{"return", {TokenType::KeywordReturn, ""}},
		{"switch", {TokenType::KeywordSwitch, ""}},
		{"default", {TokenType::KeywordDefault, ""}},
	};
	auto result = keywords.find(word);

	if (result != keywords.end()) {
		return result->second;
	} else {
		return Token(TokenType::Identifier, word);
	}
}