#include "isCombinator.h"

#include <string>
#include <set>
#include "../term/term.h"
#include "../term/application.h"
#include "../term/lambdaTerm.h"
#include "../term/var.h"


bool isCombinator::perform(term * t)
{
	boundedVars.clear();
	this->isCombinator = true;

	visit(t);
	return this->isCombinator;
}

void isCombinator::visitApplication(application * app)
{
	app->l()->accept(this);
	app->r()->accept(this);
}

void isCombinator::visitLambdaTerm(lambdaTerm * lamb)
{
	std::multiset<std::string>::iterator it;

	it = boundedVars.insert(lamb->v()->identifier());
	lamb->t()->accept(this);
	boundedVars.erase(it);
}

void isCombinator::visitVar(var * v)
{
	bool thisVarIsFree = 
		boundedVars.find(v->identifier()) == boundedVars.end();

	if( thisVarIsFree ) this->isCombinator = false;
}

