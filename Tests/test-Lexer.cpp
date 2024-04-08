#include <gtest/gtest.h>
#include <fstream>
#include <Lexer.h>

TEST(LexerTest, TestIfBlock) {
	std::ifstream sourceFile("C:\\Users\\dimas\\OneDrive\\Desktop\\Interpreter\\Tests\\source.txt");
	ASSERT_TRUE(sourceFile.is_open()) << "Неудалось открыть файл 'source.txt'";

	Lexer lexer(sourceFile);

	TokenVector tokens = lexer.tokenize();

	TokenVector expectedTokens = {
		{TokenType::Identifier, "x"},
		{TokenType::Assign, ""},
		{TokenType::ValueNumber, "1"},
		{TokenType::EndLine, ""},

		{TokenType::KeywordIf, ""},
		{TokenType::OpenParen, ""},
		{TokenType::Identifier, "x"},
		{TokenType::LessThan, ""},
		{TokenType::ValueNumber, "1"},
		{TokenType::CloseParen, ""},
		{TokenType::OpenBrace, ""},
		{TokenType::EndLine, ""},
		{TokenType::Identifier, "y"},
		{TokenType::Assign, ""},
		{TokenType::Identifier, "x"},
		{TokenType::Addition, ""},
		{TokenType::ValueNumber, "1"},
		{TokenType::EndLine, ""},
		{TokenType::CloseBrace, ""},
		{TokenType::EndLine, ""},
	};

	ASSERT_EQ(tokens.size(), expectedTokens.size());
	setlocale(LC_ALL, "RU");
	for (int i = 0; i < tokens.size(); i++) {
		EXPECT_EQ(tokens[i].getType(), expectedTokens[i].getType()) << i << ".Токены не совпадает : " << (int)tokens[i].getType() << " and " << (int)expectedTokens[i].getType() << std::endl;
		EXPECT_EQ(tokens[i].getValue(), expectedTokens[i].getValue());
	}
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}