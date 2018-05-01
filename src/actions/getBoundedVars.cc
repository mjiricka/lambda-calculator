#include "getBoundedVars.h"

#include <string>
#include <set>
#include "../term/term.h"
#include "../term/application.h"
#include "../term/lambdaTerm.h"
#include "../term/var.h"


std::set<std::string> getBoundedVars::perform(term * t)
{
	boundedVars.clear();

	visit(t);
	return boundedVars;
}

void getBoundedVars::visitApplication(application * app)
{
	app->l()->accept(this);
	app->r()->accept(this);
}

void getBoundedVars::visitLambdaTerm(lambdaTerm * lamb)
{
	boundedVars.insert(lamb->v()->identifier());
	lamb->t()->accept(this);
}

void getBoundedVars::visitVar(var *)
{
	/* do nothing */
}

