#include <Lexer.h>
#include <iostream>

Lexer::Lexer(std::wifstream& sourceFile) : sourceFile(sourceFile), currentLineIndex(0) {
}

TokenVector Lexer::tokenize() {
	std::wstring lineOfCode;
	while (std::getline(sourceFile, lineOfCode)) {
		currentLineIndex++;
		if (lineOfCode == L"") continue;
		setNewLine(lineOfCode);
		tokenizeLine();
		tokens.push_back({ TokenType::EndLine, L"" });
	}

	return tokens;
}

void Lexer::setNewLine(std::wstring& newLine) {
	currentLine.str(newLine);
	currentLine.clear(); // Сброс флагов ошибок и EOF
	currentLine.seekg(0); // Перемещение позиции чтения в начало строки
}

void Lexer::tokenizeLine() {
	while (currentLine >> currentChar) {
		if (iswdigit(currentChar)) tokenizeNumber();
		else if (__iswcsym(currentChar)) tokenizeWord();
		else if (currentChar == L'#') return;
		else tokenizeOperator();
	}
}

void Lexer::tokenizeNumber() {
	if (currentChar == L'0') {
		currentChar = currentLine.get();
		switch (currentChar) {
		case(L'x'): return tokenizeHexNumber();
		case(L'b'): return tokenizeBinNumber();
		}
	}
	tokenizeDecNumber();
}

void Lexer::tokenizeDecNumber() {
	std::wstring buffer;
	bool isHaveDot = false;
	while (iswdigit(currentChar) || currentChar == L'.') {
		buffer += currentChar;
		currentChar = currentLine.get();
		if (currentChar == L'.') {
			if (!isHaveDot) isHaveDot = true;
			else return;
		}
	}
	if (iswalpha(currentChar)) tokens.push_back({ TokenType::Invalid, getCurrentPosition() }); // Надо написать новый обработчик ошибок для слитых токенов
	else tokens.push_back({ TokenType::ValueNumber, buffer });
	currentLine.unget();
}

void Lexer::tokenizeHexNumber() {
	std::wstring buffer;
	currentChar = currentLine.get(); // Пропускаем символ "х"
	while (iswxdigit(currentChar)) {
		buffer += currentChar;
		currentChar = currentLine.get();
	}
	if (iswalpha(currentChar)) tokens.push_back({ TokenType::Invalid, getCurrentPosition() });
	else tokens.push_back({ TokenType::ValueHexNumber, buffer });
	currentLine.unget();
}

void Lexer::tokenizeBinNumber() {
	std::wstring buffer;
	currentChar = currentLine.get(); // Пропускаем символ "b"
	while (currentChar == L'0' or currentChar == L'1') {
		buffer += currentChar;
		currentChar = currentLine.get();
	}
	if (iswalpha(currentChar) or iswdigit(currentChar)) tokens.push_back({ TokenType::Invalid, getCurrentPosition() });
	else tokens.push_back({ TokenType::ValueHexNumber, buffer });
	currentLine.unget();
}

std::wstring Lexer::getCurrentPosition() {
	return std::to_wstring(currentLineIndex)+ L':' + std::to_wstring(currentLine.tellg());
}

void Lexer::tokenizeOperator() {
	switch (currentChar) {
	case L'+': return tokens.push_back({ TokenType::Addition, L"" });
	case L'-': return tokens.push_back({ TokenType::Subtraction, L"" });
	case L'*': return tokens.push_back({ TokenType::Multiplication, L"" });
	case L'/': return tokens.push_back({ TokenType::Division, L"" });
	case L'%': return tokens.push_back({ TokenType::Modulus, L"" });
	case L'(': return tokens.push_back({ TokenType::OpenParen, L"" });
	case L')': return tokens.push_back({ TokenType::CloseParen, L"" });
	case L'{': return tokens.push_back({ TokenType::OpenBrace, L"" });
	case L'}': return tokens.push_back({ TokenType::CloseBrace, L"" });
	case L'[': return tokens.push_back({ TokenType::OpenBracket, L"" });
	case L']': return tokens.push_back({ TokenType::CloseBracket, L"" });
	case L'@': return tokens.push_back({ TokenType::Insert, L"" });
	case L'=': return tokens.push_back({ TokenType::Equal, L"" });
	case L',': return tokens.push_back({ TokenType::Comma, L"" });
	case L'"': return tokenizeString();
	case L'<':
		if (currentLine.get() == L'=') return tokens.push_back({ TokenType::LessThanOrEqual, L"" });
		currentLine.unget();
		return tokens.push_back({ TokenType::LessThan, L"" });
	case L'>':
		if (currentLine.get() == L'=') return tokens.push_back({ TokenType::GreaterThanOrEqual, L"" });
		currentLine.unget();
		return tokens.push_back({ TokenType::GreaterThan, L"" });
	case L':':
		if (currentLine.get() == L'=') return tokens.push_back({ TokenType::Assign, L"" });
		currentLine.unget();
		return tokens.push_back({ TokenType::Colon, L"" });

	default:
		tokens.push_back({ TokenType::Invalid, getCurrentPosition() });
	}
}

void Lexer::tokenizeString() {
	std::wstring buffer;
	currentChar = currentLine.get(); // пропускаем открывающий '"'
	while (currentChar != L'"' and currentChar != EOF) {
		if (currentChar == L'\\') {
			handleEscapeChar(buffer);
		} else {
			buffer += currentChar;
		}
		currentChar = currentLine.get();
	}
	tokens.push_back({TokenType::ValueString, buffer });
	currentLine.ignore(1); // пропускаем закрывающий знак '"'
}

void Lexer::handleEscapeChar(std::wstring& buffer) {
	const std::wstring escapeChars = {L'n', L'a', L'b', L'r', L't'};
	currentChar = currentLine.get();
		switch (currentChar) {
		case 'n': buffer += '\n'; break;
		case 'a': buffer += '\a'; break;
		case 'b': buffer += '\b'; break;
		case 'r': buffer += '\r'; break;
		case 't': buffer += '\n'; break;
		default: buffer += currentChar;
		}
}

void Lexer::tokenizeWord() {
	std::wstring buffer;
	while (iscsym(currentChar)) {
		buffer += currentChar;
		currentChar = currentLine.get();
	}
	tokens.push_back(lookUpWordToken(buffer));
	currentLine.unget();
}

Token Lexer::lookUpWordToken(std::wstring& word) {
	const std::unordered_map<std::wstring, Token> keywords = {
		{L"if", {TokenType::KeywordIf, L""}},
		{L"elif", {TokenType::KeywordElif, L""}},
		{L"else", {TokenType::KeywordElse, L""}},
		{L"while", {TokenType::KeywordWhile, L""}},
		{L"loop", {TokenType::KeywordLoop, L""}},
		{L"stop", {TokenType::KeywordStop, L""}},
		{L"skip", {TokenType::KeywordSkip, L""}},
		{L"fnc", {TokenType::KeywordFnc, L""}},
		{L"return", {TokenType::KeywordReturn, L""}},
		{L"switch", {TokenType::KeywordSwitch, L""}},
		{L"default", {TokenType::KeywordDefault, L""}},
	};
	auto result = keywords.find(word);

	if (result != keywords.end()) {
		return result->second;
	} else {
		return Token(TokenType::Identifier, word);
	}
}