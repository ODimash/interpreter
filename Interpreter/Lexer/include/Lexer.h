#pragma once

#include <fstream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include "Token.h"

using TokenVector = std::vector<Token>;

class Lexer {
public:
	Lexer(std::wifstream& sourceFile);
	TokenVector tokenize();

private:
	TokenVector tokens;
	std::wifstream& sourceFile;
	std::wistringstream currentLine;
	wchar_t currentChar;
	int currentLineIndex;

	void setNewLine(std::wstring& newLine);
	void tokenizeLine();
	void tokenizeNumber();
	void tokenizeDecNumber();
	void tokenizeHexNumber();
	void tokenizeBinNumber();
	void tokenizeOperator();
	void tokenizeString();
	void handleEscapeChar(std::wstring& buffer);
	void tokenizeWord();
	Token lookUpWordToken(std::wstring& word);

	std::wstring getCurrentPosition();
};