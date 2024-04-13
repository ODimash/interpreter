#include "main.h"

TEST(test_parser, binary_expr_dec) {
	TokenVector inputTokens = {
		{TokenType::ValueNumber, L"55.5"},
		{TokenType::Addition, L""},
		{TokenType::ValueNumber, L"44.5"},
	};

	Parser parser(inputTokens);
	Expression* expr = parser.parse();
	double result = expr->eval();

	ASSERT_EQ(result, 55.5 + 44.5);
}

TEST(test_parserm, binary_expr_hex) {
	TokenVector inputTokens = {
		{TokenType::ValueHexNumber, L"55"},
		{TokenType::Addition, L""},
		{TokenType::ValueHexNumber, L"45"},
	};

	Parser parser(inputTokens);
	Expression* expr = parser.parse();
	double result = expr->eval();

	ASSERT_EQ(result, 0x55 + 0x45);
}

TEST(test_parserm, binary_expr_bin) {
	TokenVector inputTokens = {
		{TokenType::ValueBinNumber, L"101101"},
		{TokenType::Addition, L""},
		{TokenType::ValueBinNumber, L"1010111"},
	};

	Parser parser(inputTokens);
	Expression* expr = parser.parse();
	double result = expr->eval();

	ASSERT_EQ(result, 0b101101 + 0b1010111);
}

TEST(test_parser, multi_expr) {
	TokenVector inputTokens = {
		{TokenType::ValueNumber, L"45"},
		{TokenType::Addition, L""},
		{TokenType::ValueNumber, L"12"},
		{TokenType::Multiplication, L""},
		{TokenType::ValueHexNumber, L"AA"},
		{TokenType::Division, L""},
		{TokenType::ValueBinNumber, L"10000"},
	};

	Parser parser(inputTokens);
	Expression* expr = parser.parse();
	double result = expr->eval();

	ASSERT_EQ(result, 45.0 + 12.0 * 0xAA / 0b10000);
}

TEST(test_parser, parantheses) {
	TokenVector inputTokens = {
		{TokenType::OpenParen, L""},
		{TokenType::ValueNumber, L"45"},
		{TokenType::Addition, L""},
		{TokenType::ValueNumber, L"12"},
		{TokenType::CloseParen, L""},

		{TokenType::Multiplication, L""},
		{TokenType::ValueHexNumber, L"AA"},
		{TokenType::Division, L""},
		{TokenType::ValueBinNumber, L"10000"},
	};


	Parser parser(inputTokens);
	Expression* expr = parser.parse();
	double result = expr->eval();

	ASSERT_EQ(result, (45.0 + 12.0) * 0xAA / 0b10000);
}