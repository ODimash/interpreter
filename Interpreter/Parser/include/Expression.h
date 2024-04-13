#pragma once
#include <Lexer.h>

class Expression {
public:
	virtual double eval() = 0;
};