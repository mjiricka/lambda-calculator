#ifndef __IS_COMBINATOR_H__
#define __IS_COMBINATOR_H__

#include <string>
#include <set>
#include "termVisitor.h"

class term;
class application;
class lambdaTerm;
class var;


class isCombinator : public termVisitor
{
public:
	bool perform(term * t);

	void visitApplication(application * app);
	void visitLambdaTerm(lambdaTerm * lamb);
	void visitVar(var * v);

private:
	std::multiset<std::string> boundedVars;
	bool isCombinator;
};

#endif
