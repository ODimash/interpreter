#include "main.h"

TEST(test_expression, binary_expression) {
	NumberExpression number1(14.7), number2(23.4);

	double addingResult = BinaryExpression(&number1, &number2, TokenType::Addition).eval();
	double substractionResult = BinaryExpression(&number1, &number2, TokenType::Subtraction).eval();
	double multiplicationResult = BinaryExpression(&number1, &number2, TokenType::Multiplication).eval();
	double divisionResult = BinaryExpression(&number1, &number2, TokenType::Division).eval();

	ASSERT_EQ(addingResult, 14.7 + 23.4);
	ASSERT_EQ(substractionResult, 14.7 - 23.4);
	ASSERT_EQ(multiplicationResult, 14.7 * 23.4);
	ASSERT_EQ(divisionResult, 14.7 / 23.4);
}

TEST(test_expression, multi_expressions) {
	NumberExpression number1(13), number2(44.1), number3(87.9);

	double result = BinaryExpression(new BinaryExpression(&number1, &number2, TokenType::Addition), &number3, TokenType::Multiplication).eval();

	ASSERT_EQ(result, (13 + 44.1)*87.9);
}