#ifndef __PRINT_DE_BRUIJN_H_
#define __PRINT_DE_BRUIJN_H_

#include "termVisitor.h"
#include <vector>
#include <string>

class application;
class lambdaTerm;
class var;

class printDeBruijn : public termVisitor
{
public:
	void visitApplication(application * app);
	void visitLambdaTerm(lambdaTerm * lamb);
	void visitVar(var * v);
	
	std::string perform(term * t);

private:
	std::string result;
	std::vector<var *> boundVariables;
};

#endif
