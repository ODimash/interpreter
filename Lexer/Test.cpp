#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <Lexer.h>

std::string getTokenTypeName(TokenType type);

using namespace std;

int main() {
	std::setlocale(LC_ALL, "RU");
	std::ifstream sourceFile("C:\\Users\\dimas\\OneDrive\\Desktop\\Interpreter\\test.txt");
	if (!sourceFile.is_open()) {
		cerr << "Can't open file" << endl;
		return 1;
	}

	string codeLine;
	string sourceCode;
	while (getline(sourceFile, codeLine)) {
		sourceCode += codeLine + '\n';
	}
	sourceCode += EOF;

	cout << sourceCode << endl;
	Lexer lexer(sourceCode);
	std::vector<Token> tokens = lexer.tokenize();

	for (auto token : tokens) {
		cout << "{ Token type: " << getTokenTypeName(token.type) << ", Text: " << token.text << " }" << endl;
	}

	return 0;
}



std::string getTokenTypeName(TokenType type) {
	// —татический массив строк с названи€ми токенов
	static std::array<std::string, static_cast<size_t>(TokenType::END_OF_FILE) + 1> tokenNames = {
		"IDENTIFIER_VAR",
		"IDENTIFIER_ARREY",
		"IDENTIFIER_FUNC",

		"PLUS",
		"MINUS",
		"MULTIPLY",
		"DIVIDE",
		"ASSIGN",
		"REMAINDER",
		"EQUAL",
		"NOT_EQUAL",
		"LESS_THAN",
		"LESS_THAN_OR_EQUAL",
		"GREATER_THAN",
		"GREATER_THAN_OR_EQUAL",
		"AND",
		"OR",
		"NOT",
		"SEMICOLON",
		"COMMA",
		"LEFT_PAREN",
		"RIGHT_PAREN",
		"LEFT_BRACE",
		"RIGHT_BRACE",
		"IF",
		"ELSE",
		"WHILE",
		"FOR",
		"LOOP",
		"RETURN",
		"FUNCTION",
		"VAR",
		"ARRAY",
		"INT",
		"FLOAT",
		"HEX",
		"BINARY",
		"BOOL",
		"CHAR",
		"STRING",
		"NONE",
		"TRUE",
		"FALSE",
		"MSGBOX",
		"INPUTBOX",
		"INVALIDE_TYPE",
		"END_OF_LINE",
		"COMMENT",
		"END_OF_FILE"
	};

	// ≈сли тип токена находитс€ в диапазоне перечислени€, возвращаем соответствующее название
	if (static_cast<size_t>(type) < tokenNames.size()) {
		return tokenNames[static_cast<size_t>(type)];
	} else {
		return "UNKNOWN_TOKEN_TYPE"; // Ќеизвестный тип токена
	}
}
