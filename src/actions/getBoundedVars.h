#ifndef __GET_BOUNDED_VARS__
#define __GET_BOUNDED_VARS__

#include <string>
#include <set>
#include "termVisitor.h"

class term;
class application;
class lambdaTerm;
class var;


class getBoundedVars : public termVisitor
{
public:
	std::set<std::string> perform(term * t);

	void visitApplication(application * app);
	void visitLambdaTerm(lambdaTerm * lamb);
	void visitVar(var *);

private:
	std::set<std::string> boundedVars;
};

#endif
