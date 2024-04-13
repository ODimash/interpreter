#include "main.h"

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
	Token(TokenType::ValueString, L"this is string?"),
	Token(TokenType::EndLine, L""),

	Token(TokenType::Identifier, L"text_3"),
	Token(TokenType::Assign, L""),
	Token(TokenType::ValueString, L"for writing on a new line past '\\' from 'n', \n This is a character for new line - \\n"),
	Token(TokenType::EndLine, L"")
	};

	/*for (int i = 0; i < tokens.size(); i++) {
		std::wcerr << "token 1: { " << (int)tokens[i].getType() << L":" << tokens[i].getValue() << " }" << std::endl;
		std::wcerr << "token 2: { " << (int)expectedTokens[i].getType() << L":" << expectedTokens[i].getValue() << " }" << std::endl;
	}*/

	ASSERT_EQ(tokens.size(), expectedTokens.size());
	for (int i = 0; i < tokens.size(); i++) {
		EXPECT_EQ(tokens[i].getType(), expectedTokens[i].getType());
		EXPECT_EQ(tokens[i].getValue(), expectedTokens[i].getValue());
	}
}
