#include "printFormally.h"

#include <string>
#include "../term/application.h"
#include "../term/lambdaTerm.h"
#include "../term/var.h"


void printFormally::visitApplication(application * app)
{
	bool printBraces;

	printBraces = dynamic_cast<var *>(app->l()) == NULL;
	if( printBraces ) result += '(';
	app->l()->accept(this);
	if( printBraces ) result += ')';
	
	printBraces = dynamic_cast<var *>(app->r()) == NULL;
	if( printBraces ) result += '(';
	app->r()->accept(this);
	if( printBraces ) result += ')';
}

void printFormally::visitLambdaTerm(lambdaTerm * lamb)
{
	result += '\\';
	lamb->v()->accept(this);
	result += ".(";
	lamb->t()->accept(this);
	result += ')';
}

void printFormally::visitVar(var * v)
{
	result += v->identifier();
}

std::string printFormally::perform(term * t)
{
	result.clear();

	visit(t);

	return result;
}

