#ifndef __TERM_VISITOR_H_
#define __TERM_VISITOR_H_

class term;
class application;
class lambdaTerm;
class var;

class termVisitor
{
public:
	virtual void visitApplication(application * app) = 0;
	virtual void visitLambdaTerm(lambdaTerm * lamb) = 0;
	virtual void visitVar(var * v) = 0;
	
	void visit(term * t);

protected:
	termVisitor();
};

inline termVisitor::termVisitor() { /* nothing */ }

#endif
