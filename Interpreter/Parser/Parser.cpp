#include "Parser.h"

Parser::Parser(TokenVector tokens) : tokens(tokens), currentTokenId(0) {
}

Expression* Parser::parse() {
	Expression* expr;
	expr = expression();

	return expr;
}

Expression* Parser::expression() {
	return addition();
}

Expression* Parser::addition() {
	Expression* expr = multiplication();
	while (true) {
		if (match(TokenType::Addition))
			expr = new BinaryExpression(expr, multiplication(), TokenType::Addition);
		else if (match(TokenType::Subtraction))
			expr = new BinaryExpression(expr, multiplication(), TokenType::Subtraction);
		else break;
	}
	return expr;
}



Expression* Parser::multiplication() {
	Expression* expr = primary();
	while (true) {
		if (match(TokenType::Multiplication))
			expr = new BinaryExpression(expr, primary(), TokenType::Multiplication);
		else if (match(TokenType::Division))
			expr = new BinaryExpression(expr, primary(), TokenType::Division);
		else break;
	}
	return expr;
}

Expression* Parser::unary() {
	return nullptr;
}

Expression* Parser::primary() {
	Token currentToken = peekToken();

	if (match(TokenType::ValueNumber))
		return new NumberExpression(stod(currentToken.getValue()));
	if (match(TokenType::ValueHexNumber))
		return new NumberExpression(stol(currentToken.getValue(), nullptr, 16));
	if (match(TokenType::ValueBinNumber))
		return new NumberExpression(stol(currentToken.getValue(), nullptr, 2));
	if (match(TokenType::OpenParen)) {
		Expression* expr = expression();
		match(TokenType::CloseParen);
		return expr;
	}
	return nullptr;
}

bool Parser::isAtEnd() {
	return currentTokenId >= tokens.size();
}

bool Parser::match(TokenType expectedTokenType) {
	if (isAtEnd())
		return false;
	if (expectedTokenType != tokens[currentTokenId].getType())
		return false;
	currentTokenId++;
	return true;
}

Token Parser::getToken() {
	return tokens.at(currentTokenId++);
}

Token Parser::peekToken() {
	return tokens.at(currentTokenId);
}