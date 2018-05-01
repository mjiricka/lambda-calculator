#include "scanner.h"

#include <iostream>
#include <cctype>
#include <istream>
#include "__parser.h"


Scanner::Scanner(std::istream & input)
	: input(input)
{ }

int Scanner::yylex()
{
	int i = nextToken();
	//std::cout << '[' << i << ',' << (char) _tokenValue << ']' << std::endl;
	return i;
}

int Scanner::nextToken()
{
	char c;

	// skip whitespaces
	while( input.get(c) && c != '\n' && isspace(c) );

	// end of stream
	if( input.eof() )
		return 0;
	
	// end of line
	switch( c )
	{
		case '\n':
			return Parser::EOLN;

		case '\\':
			return Parser::LAMBDA;
		
		case '.':
			return Parser::DOT;

		case '(':
			return Parser::LEFT_PARENTHESE;

		case ')':
			return Parser::RIGHT_PARENTHESE;
	
		case '[':
			return Parser::LEFT_BRACKET;

		case ']':
			return Parser::RIGHT_BRACKET;

		case '=':
			return Parser::EQUAL;

		case '+':
			return Parser::ADDITION;

		case '*':
			return Parser::MULTIPLICATION;

		case '-':
			return Parser::SUBTRACTION;

		case '<':
			return Parser::LESS_OR_EQUAL;

		case '?':
			return Parser::IS_ZERO;
	}

	// digit
	if( isdigit(c) )
	{
		input.putback(c);
		input >> _tokenValue;
		return Parser::NUMBER;
	}

	// character
	if( isalpha(c) )
	{
		_tokenValue = c;

		if( islower(c) )
			return Parser::CHAR;

		switch(c)
		{
			case 'T':
				return Parser::TRUE;
				break;
			case 'F':
				return Parser::FALSE;
				break;
			case 'A':
				return Parser::AND;
				break;
			case 'O':
				return Parser::OR;
				break;
			case 'N':
				return Parser::NEG;
				break;
		}
	}

	// error
	return -1;
}

int Scanner::tokenValue() {
	return _tokenValue;
}

