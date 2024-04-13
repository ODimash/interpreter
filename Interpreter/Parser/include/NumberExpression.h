#pragma once

#include "Expression.h"

class NumberExpression : public Expression{
public:
	NumberExpression(double number);
	double eval() override;

private:
	double number;
};