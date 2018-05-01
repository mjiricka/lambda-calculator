#include "evaluateLazily.h"

#include "../term/application.h"
#include "../term/lambdaTerm.h"
#include "../term/var.h"
#include "../actions/actions.h"


term * evaluateLazily::perform(term * t, bool & limitExceeded, bool stopAtLambda, int limit)
{
	this->stopAtLambda = stopAtLambda;
	term * reducedT = t->clone();

	do
	{
		wasReduced = false;
		reducedT->accept(this);
		delete reducedT;
		reducedT = result;
		--limit;
	}
	while( wasReduced && limit > 0 );

	limitExceeded = limit == 0;

	return reducedT;
}

void evaluateLazily::visitApplication(application * app)
{
	lambdaTerm * lt = dynamic_cast<lambdaTerm *>(app->l()); 
	
	if( lt != NULL && !wasReduced ) // Application on lambda term - we can reduce!
	{
		result = actions::substitute( lt->t(), lt->v(), app->r() );
		wasReduced = true;
	}
	else
	{
		// We have to go left first.
		app->l()->accept(this);
		term * l = result;

		app->r()->accept(this);
		term * r = result;

		result = new application(l,r);
	}
}

void evaluateLazily::visitLambdaTerm(lambdaTerm * lamb)
{
	if( stopAtLambda )
	{
		result = lamb->clone();
	}
	else
	{
		lamb->t()->accept(this);
		result = new lambdaTerm( (var *) lamb->v()->clone(), result);
	}
}

void evaluateLazily::visitVar(var * v)
{
	result = v->clone();
}

