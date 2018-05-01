#include "toCombinatorialTerm.h"

#include "actions.h"
#include "../term/application.h"
#include "../term/lambdaTerm.h"
#include "../term/var.h"


void toCombinatorialTerm::visitApplication(application * app)
{
	// T[(E1 E2)] => (T[E1] T[E2])

	app->l()->accept(this);
	term * l = result;
	app->r()->accept(this);
	term * r = result;

	result = new application(l,r);
}

void toCombinatorialTerm::visitLambdaTerm(lambdaTerm * lamb)
{
	// T[\x.x] => I
	var * v = dynamic_cast<var*>(lamb->t());
	if( (v != NULL) && (lamb->v()->identifier() == v->identifier()) )
	{
		result = new var('I');
		return;
	}

	// T[\x.E] => (K T[E]) (if x does not occur free in E)
	if( actions::getFreeVars( lamb->t() ).count(lamb->v()->identifier()) == 0 )
	{
		visit( lamb->t() );
		result = new application(
			new var('K'),
			result
		);
		return;
	}
	else
	{
		// T[\x.\y.E] => T[\x.T[\y.E]] (if x occurs free in E)
		lambdaTerm * lt = dynamic_cast<lambdaTerm*>(lamb->t());
		if( lt )
		{
			visit(lt);
			term * t = result;
			
			term * ltTmp = new lambdaTerm(
				(var *) lamb->v()->clone(),
				t
			);

			visit(ltTmp);
			delete ltTmp;

			return;
		}
	}

	// T[\x.(E1 E2)] => (S T[\x.E1] T[\x.E2])
	application * a = dynamic_cast<application*>(lamb->t());
	if( a != NULL )
	{
		// E1
		lambdaTerm * l1 = new lambdaTerm(
			(var *) lamb->v()->clone(),
			a->l()->clone()
		);
		visit(l1);
		term * e1 = result;
		delete l1;

		// E2
		lambdaTerm * l2 = new lambdaTerm(
			(var *) lamb->v()->clone(),
			a->r()->clone()
		);
		visit(l2);
		term * e2 = result;
		delete l2;

		// result
		result =
			new application(
				new application(
					new var('S'),
					e1
				),
				e2 );

		return;
	}
}

void toCombinatorialTerm::visitVar(var * v)
{
	// T[x] => x
	result = v->clone();
}

term * toCombinatorialTerm::perform(term * t)
{
	visit(t);
	return result;
}

