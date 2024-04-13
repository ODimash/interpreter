#include "BinaryExpression.h"

BinaryExpression::BinaryExpression(Expression* expr1, Expression* expr2, TokenType operation) 
	: expr1(expr1), expr2(expr2), operation(operation)
{
	this->expr1 = expr1;
}

double BinaryExpression::eval() {
	switch (operation) {
	case TokenType::Addition: return expr1->eval() + expr2->eval();
	case TokenType::Subtraction: return expr1->eval() - expr2->eval();
	case TokenType::Multiplication: return expr1->eval() * expr2->eval();
	case TokenType::Division: return expr1->eval() / expr2->eval();
	default:
		throw "Invalide operator";
	}
}