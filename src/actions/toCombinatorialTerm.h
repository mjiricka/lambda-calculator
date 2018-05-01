#ifndef __TO_COMBINATORIAL_TERM_H_
#define __TO_COMBINATORIAL_TERM_H_

#include "termVisitor.h"

class application;
class lambdaTerm;
class var;

class toCombinatorialTerm : public termVisitor
{
public:
	void visitApplication(application * app);
	void visitLambdaTerm(lambdaTerm * lamb);
	void visitVar(var * v);
	
	term * perform(term * t);

private:
	term * result;
};

#endif
