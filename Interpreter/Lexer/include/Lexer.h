#pragma once

#include <fstream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include "Token.h"

using TokenVector = std::vector<Token>;

class Lexer {
public:
	Lexer(std::ifstream& sourceFile);
	TokenVector tokenize();

private:
	TokenVector tokens;
	std::ifstream& sourceFile;
	std::istringstream currentLine;
	char currentChar;
	int currentLineIndex;

	void setNewLine(std::string& newLine);
	void tokenizeLine();
	void tokenizeNumber();
	void tokenizeDecNumber();
	void tokenizeHexNumber();
	void tokenizeBinNumber();
	void tokenizeOperator();
	void tokenizeString();
	void handleEscapeChar(std::string& buffer);
	void tokenizeWord();
	Token lookUpWordToken(std::string& word);

	std::string getCurrentPosition();
};