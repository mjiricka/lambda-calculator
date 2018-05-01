#include "printJavaScript.h"

#include <vector>
#include <string>
#include <set>
#include "../term/application.h"
#include "../term/lambdaTerm.h"
#include "../term/var.h"
#include "actions.h"


std::string printJavaScript::perform(term * t)
{
	result.clear();

	std::set<std::string> freeVars = actions::getFreeVars(t);
	if( !freeVars.empty() )
	{
		result += "var ";			
		std::set<std::string>::iterator it;
		for( it = freeVars.begin(); it != freeVars.end(); ++it )
			 result += *it + ',';
		result[ result.size()-1 ] = ';';
		result += '\n';
	}

	visit(t);
	
	result += '\n';
	return result;
}

void printJavaScript::visitApplication(application * app)
{
	//bool printBraces;

	//printBraces = dynamic_cast<var *>(app->l()) == NULL;
	//if( printBraces ) result += '(';
	app->l()->accept(this);
	//if( printBraces ) result += ')';
	
	//printBraces = dynamic_cast<var *>(app->r()) == NULL;
	//if( printBraces )
	result += '(';
	app->r()->accept(this);
	//if( printBraces )
	result += ')';
}

void printJavaScript::visitLambdaTerm(lambdaTerm * lamb)
{
	result += "function(";
	lamb->v()->accept(this);
	result += "){return ";
	lamb->t()->accept(this);
	result += "}";
}

void printJavaScript::visitVar(var * v)
{
	result += v->identifier();
}

