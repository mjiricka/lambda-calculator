#ifndef __SUBSTITUTE_H_
#define __SUBSTITUTE_H_

#include "termVisitor.h"
#include <string>
#include <set>

class term;
class application;
class lambdaTerm;
class var;

class substitute : public termVisitor
{
public:
	term * perform(term * t, var * from, term * to);

	void visitApplication(application * app);
	void visitLambdaTerm(lambdaTerm * lamb);
	void visitVar(var * v);

private:
	var * from;
	term * to;
	term * lastTerm;
	std::set<std::string> toFreeVars;
	
	std::string getUniqIdentifier
	(std::set<std::string> & usedIdentifiers1, std::set<std::string> & usedIdentifiers2);
};

#endif
