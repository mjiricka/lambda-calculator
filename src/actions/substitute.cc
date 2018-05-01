#include "substitute.h"

#include <iostream>
#include <string>
#include <set>
#include "../term/term.h"
#include "../term/application.h"
#include "../term/lambdaTerm.h"
#include "../term/var.h"
#include "actions.h"


term * substitute::perform(term * t, var * from, term * to)
{
	this->from = from;
	this->to = to;
	this->toFreeVars = actions::getFreeVars(to);
	visit(t);

	return lastTerm;
}

void substitute::visitApplication(application * app)
{
	app->l()->accept(this);
	term * newL = lastTerm;

	app->r()->accept(this);
	term * newR = lastTerm;

	lastTerm = new application(newL, newR);
}

void substitute::visitLambdaTerm(lambdaTerm * lamb)
{
	// (\x.t)[x=..] = (\x.t)
	if( lamb->v()->identifier() == from->identifier() )
	{
		lastTerm = lamb->clone();
		return;
	}

	// Check if substitution is possible.
	bool needRename
		= toFreeVars.find(lamb->v()->identifier()) != toFreeVars.end();

	if( needRename )
	{
		// Find uniq identifier.
		std::set<std::string> fv = actions::getFreeVars(lamb->t());
		std::string newName = getUniqIdentifier(toFreeVars, fv);
		// No uniq identifier available.
		if( newName.length() == 0 )
		{
			newName = lamb->v()->identifier();
			std::cout << "Error: No uniq identifier left." << std::endl;
		}

		// Rename variable on a clone.
		term * tmp = lamb->t()->clone();
		actions::rename(tmp, lamb->v()->identifier(), newName);

		// Continue on the clone.
		tmp->accept(this);
		// Clone was cloned, clean up.
		delete tmp;

		// Return
		lastTerm = new lambdaTerm( new var(newName), lastTerm );
	}
	else
	{
		// This lambda term is OK, continue to subterm.
		lamb->t()->accept(this);
		lastTerm = new lambdaTerm((var *)lamb->v()->clone(), lastTerm);
	}
}

void substitute::visitVar(var * v)
{
	if( v->identifier() == from->identifier() )
		lastTerm = to->clone();
	else
		lastTerm = v->clone();
}

// Find character(a-z) that is not present either in usedIdentifiers1 and usedIdentifiers2.
std::string substitute::getUniqIdentifier
(std::set<std::string> & usedIdentifiers1, std::set<std::string> & usedIdentifiers2)
{
	std::string uniq("a");

	do
	{
		bool isUniq1 = usedIdentifiers1.find(uniq) == usedIdentifiers1.end();
		bool isUniq2 = usedIdentifiers2.find(uniq) == usedIdentifiers2.end();
		if( isUniq1 && isUniq2 ) return uniq;
	}
	while(++(uniq[0]) <= 'z');

	return std::string();
}

