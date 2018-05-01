#include "rename.h"

#include <string>
#include "../term/application.h"
#include "../term/lambdaTerm.h"
#include "../term/var.h"

void tmpNamespace::rename::visitApplication(application * app)
{
	app->l()->accept(this);
	app->r()->accept(this);
}

void tmpNamespace::rename::visitLambdaTerm(lambdaTerm * lamb)
{
	//if( lamb->v()->identifier() == what )
	//	lamb->v()->set_identifier(on);

	if( lamb->v()->identifier() != what )
		lamb->t()->accept(this);
}

void tmpNamespace::rename::visitVar(var * v)
{
	if( v->identifier() == what )
		v->set_identifier(on);
}

void tmpNamespace::rename::perform(term * t, std::string what, std::string on)
{
	this->what = what;
	this->on = on;
	t->accept(this);
}

