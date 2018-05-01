#ifndef __PRINT_FORMALLY_H_
#define __PRINT_FORMALLY_H_

#include "termVisitor.h"
#include <string>

class term;
class application;
class lambdaTerm;
class var;

class printFormally : public termVisitor
{
public:
	void visitApplication(application * app);
	void visitLambdaTerm(lambdaTerm * lamb);
	void visitVar(var * v);
	
	std::string perform(term * t);

private:
	std::string result;
};

#endif
