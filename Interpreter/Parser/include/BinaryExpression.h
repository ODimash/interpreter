#pragma once

#include <Lexer.h>
#include "Expression.h"

class BinaryExpression : public Expression {
public:
	BinaryExpression(Expression* expr1, Expression* expr2, TokenType operation);
	double eval() override;

private:
	Expression* expr1;
	Expression* expr2;
	TokenType operation;
};