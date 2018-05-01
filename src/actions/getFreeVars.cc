#include "getFreeVars.h"

#include <string>
#include <set>
#include "../term/term.h"
#include "../term/application.h"
#include "../term/lambdaTerm.h"
#include "../term/var.h"


std::set<std::string> getFreeVars::perform(term * t)
{
	freeVars.clear();
	boundedVars.clear();

	visit(t);
	return freeVars;
}

void getFreeVars::visitApplication(application * app)
{
	app->l()->accept(this);
	app->r()->accept(this);
}

void getFreeVars::visitLambdaTerm(lambdaTerm * lamb)
{
	std::multiset<std::string>::iterator it;

	it = boundedVars.insert(lamb->v()->identifier());
	lamb->t()->accept(this);
	boundedVars.erase(it);
}

void getFreeVars::visitVar(var * v)
{
	bool thisVarIsFree = 
		boundedVars.find(v->identifier()) == boundedVars.end();

	if( thisVarIsFree )
		freeVars.insert(v->identifier());
}

