#ifndef __VAR_H_
#define __VAR_H_

#include <string>
#include "term.h"

class termVisitor;


class var : public term
{
public:
	explicit var(std::string identifier);
	explicit var(char identifier);
	~var();
	term * clone();
	
	void accept(termVisitor * v);

	std::string identifier();
	void set_identifier(std::string newIdentifier);

private:
	std::string _identifier;
};

#endif
