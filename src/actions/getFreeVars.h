#ifndef __GET_FREE_VARS__
#define __GET_FREE_VARS__

#include <string>
#include <set>
#include "termVisitor.h"

class term;
class application;
class lambdaTerm;
class var;


class getFreeVars : public termVisitor
{
public:
	std::set<std::string> perform(term * t);

	void visitApplication(application * app);
	void visitLambdaTerm(lambdaTerm * lamb);
	void visitVar(var * v);

private:
	std::set<std::string> freeVars;
	std::multiset<std::string> boundedVars;
};

#endif
