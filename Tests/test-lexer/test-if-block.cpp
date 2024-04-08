#include "main.h"

TEST(LexerTest, TestIfBlock) {
	std::wifstream sourceFile("C:\\Users\\dimas\\OneDrive\\Desktop\\Interpreter\\Tests\\test-codes\\if-block.jt");
	ASSERT_TRUE(sourceFile.is_open()) << "Неудалось открыть файл 'source.txt'";

	Lexer lexer(sourceFile);

	TokenVector tokens = lexer.tokenize();

	TokenVector expectedTokens = {
		{TokenType::Identifier, L"x"},
		{TokenType::Assign, L""},
		{TokenType::ValueNumber, L"1"},
		{TokenType::EndLine, L""},

		{TokenType::KeywordIf, L""},
		{TokenType::OpenParen, L""},
		{TokenType::Identifier, L"x"},
		{TokenType::LessThan, L""},
		{TokenType::ValueNumber, L"1"},
		{TokenType::CloseParen, L""},
		{TokenType::OpenBrace, L""},
		{TokenType::EndLine, L""},
		{TokenType::Identifier, L"y"},
		{TokenType::Assign, L""},
		{TokenType::Identifier, L"x"},
		{TokenType::Addition, L""},
		{TokenType::ValueNumber, L"1"},
		{TokenType::EndLine, L""},
		{TokenType::CloseBrace, L""},
		{TokenType::EndLine, L""},
	};


	EXPECT_EQ(tokens.size(), expectedTokens.size());
	setlocale(LC_ALL, "RU");
	for (int i = 0; i < tokens.size(); i++) {
		EXPECT_EQ(tokens[i].getType(), expectedTokens[i].getType()) << i << ".Токены не совпадает : " << (int)tokens[i].getType() << " and " << (int)expectedTokens[i].getType() << std::endl;
		EXPECT_EQ(tokens[i].getValue(), expectedTokens[i].getValue());
	}
}
