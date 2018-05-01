#ifndef __EVALUATE_LAZILY_H__
#define __EVALUATE_LAZILY_H__

#include "termVisitor.h"

class term;
class application;
class lambdaTerm;
class var;


class evaluateLazily : public termVisitor
{
public:
	term * perform(term * t, bool & limitExceeded, bool stopAtLambda, int limit);

	void visitApplication(application * app);
	void visitLambdaTerm(lambdaTerm * lamb);
	void visitVar(var * v);

private:
	term * result;
	bool wasReduced;
	bool stopAtLambda;
};

#endif
