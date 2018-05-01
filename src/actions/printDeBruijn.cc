#include "printDeBruijn.h"

#include <vector>
#include <string>
#include <sstream>
#include "../term/application.h"
#include "../term/lambdaTerm.h"
#include "../term/var.h"


void printDeBruijn::visitApplication(application * app)
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

void printDeBruijn::visitLambdaTerm(lambdaTerm * lamb)
{
	boundVariables.push_back(lamb->v());

	result += "\\.(";
	lamb->t()->accept(this);
	result += ')';

	boundVariables.pop_back();
}

void printDeBruijn::visitVar(var * v)
{
	std::vector<var *>::reverse_iterator it = boundVariables.rbegin();

	// Count after how many lambdas is this variable bounded.
	size_t idx = 0;
	while( (boundVariables.rend() != it) && ((*it++)->identifier() != v->identifier()) )
		++idx;

	if( boundVariables.size() == idx ) // Variable is free.
		result += v->identifier();
	else // Variable is bounded.
	{
		// Convert int to string and append.
		std::stringstream ss;
		ss << idx;
		result += ss.str();
	}
}

std::string printDeBruijn::perform(term * t)
{
	result.clear();

	visit(t);

	return result;
}

