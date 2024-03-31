// Interpreter.cpp: определяет точку входа для приложения.
//

#include "Interpreter.h"

using namespace std;

int main() {
	std::ifstream sourceFile("C:\\Users\\dimas\\OneDrive\\Desktop\\Interpreter\\test.txt");
	if (!sourceFile.is_open()) {
		cerr << "Can't open file" << endl;
		return 1;
	}

	string codeLine;
	string sourceCode;
	while (getline(sourceFile, codeLine)) {
		sourceCode += '\n' + codeLine;
	}
	cout << sourceCode << endl;
	Lexer lexer(sourceCode);
	std::vector<Token> tokens = lexer.tokenize();

	for (auto token : tokens) {
		cout << " {Token type: " << static_cast<int>(token.type) << ", Text: " << token.text << " }" << endl;
	}

	return 0;
}
