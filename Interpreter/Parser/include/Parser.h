#include <Lexer.h>
#include <string>
#include "BinaryExpression.h"
#include "NumberExpression.h"

class Parser {
public:
	Parser(TokenVector tokens);
	Expression* parse();

private:
	TokenVector tokens;
	int currentTokenId;

	bool isAtEnd();
	bool match(TokenType expectedTokenType);
	Token getToken();
	Token peekToken();

	Expression* expression();
	Expression* addition();
	Expression* multiplication();
	Expression* unary();
	Expression* primary();
};