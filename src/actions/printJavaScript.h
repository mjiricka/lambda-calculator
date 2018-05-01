#ifndef __PRINT_JAVA_SCRIPT_H_
#define __PRINT_JAVA_SCRIPT_H_

#include "termVisitor.h"
#include <string>

class application;
class lambdaTerm;
class var;

class printJavaScript : public termVisitor
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
