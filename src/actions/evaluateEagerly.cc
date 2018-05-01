#include "evaluateEagerly.h"

#include "../term/application.h"
#include "../term/lambdaTerm.h"
#include "../term/var.h"
#include "../actions/actions.h"


term * evaluateEagerly::perform(term * t, bool & limitExceeded, bool stopAtLambda, int limit)
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

void evaluateEagerly::visitApplication(application * app)
{
	// We have to go right first.
	app->r()->accept(this);

	if( wasReduced )
	{
		result = new application( app->l()->clone(), result);
	}
	else
	{
		delete result;

		// Nothing on right, look here.
		lambdaTerm * lt = dynamic_cast<lambdaTerm *>(app->l()); 
	
		if( lt != NULL && !wasReduced ) // Application on lambda term - we can reduce!
		{
			result = actions::substitute( lt->t(), lt->v(), app->r() );
			wasReduced = true;
		}
		else
		{
			// Nothing to do here at all...
			result = app->clone();
		}
	}
}

void evaluateEagerly::visitLambdaTerm(lambdaTerm * lamb)
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

void evaluateEagerly::visitVar(var * v)
{
	result = v->clone();
}

