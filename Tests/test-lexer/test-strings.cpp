#include "main.h"

#ifdef WIN32
#include <Windows.h>
#endif

TEST(LexerTest, Test_strings) {
	std::wifstream sourceFile("C:\\Users\\dimas\\OneDrive\\Desktop\\Interpreter\\Tests\\test-codes\\strings.jt");
	Lexer lexer(sourceFile);
	auto tokens = lexer.tokenize();

	std::vector<Token> expectedTokens = {
	Token(TokenType::Identifier, L"text_1"),
	Token(TokenType::Assign, L""),
	Token(TokenType::ValueString, L"this is a test string"),
	Token(TokenType::EndLine, L""),

	Token(TokenType::Identifier, L"text_2"),
	Token(TokenType::Assign, L""),
	Token(TokenType::ValueString, L"Это тестовая строка"),
	Token(TokenType::EndLine, L""),

	Token(TokenType::Identifier, L"text_3"),
	Token(TokenType::Assign, L""),
	Token(TokenType::ValueString, L"Для вставки двойных ковычек, поставьте \\ перед 'n', \n А для переноса строки \\n"),
	Token(TokenType::EndLine, L"")
	};

	SetConsoleOutputCP(CP_UTF8);
	for (int i = 0; i < tokens.size(); i++)
		std::wcerr << "{ " << (int)tokens[i].getType() << L":" << tokens[i].getValue() << " }" << std::endl;

	ASSERT_EQ(tokens.size(), expectedTokens.size());
	for (int i = 0; i < tokens.size(); i++) {
		EXPECT_EQ(tokens[i].getType(), expectedTokens[i].getType());
		EXPECT_EQ(tokens[i].getValue(), expectedTokens[i].getValue());
	}
}
