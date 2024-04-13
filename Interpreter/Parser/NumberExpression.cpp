#include "NumberExpression.h"

NumberExpression::NumberExpression(double number) : number(number) {
}

double NumberExpression::eval() {
	return number;
}