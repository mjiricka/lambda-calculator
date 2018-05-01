#ifndef _SCANNER_H_
#define _SCANNER_H_

#include <istream>

class Scanner
{
public:
	explicit Scanner(std::istream & input);
	int yylex();
	int nextToken();
	int tokenValue();

private:
	int _tokenValue;
	std::istream & input;
};

#endif

