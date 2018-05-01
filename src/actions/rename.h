#ifndef __RENAME_H_
#define __RENAME_H_

#include <string>
#include "termVisitor.h"

class application;
class lambdaTerm;
class var;

/*
	Some name collision with readline library.
	I am not sure how resolve it elegantly,
	so I wrapped class into a namespace.
*/

namespace tmpNamespace
{
class rename : public termVisitor
{
public:
	void visitApplication(application * app);
	void visitLambdaTerm(lambdaTerm * lamb);
	void visitVar(var * v);
	
	void perform(term * t, std::string what, std::string on);

private:
	std::string what;
	std::string on;
};
}
#endif
