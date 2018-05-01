#ifndef __ACTIONS_H_
#define __ACTIONS_H_

#include <string>
#include "printDeBruijn.h"
#include "printFormally.h"
#include "toCombinatorialTerm.h"
#include "printJavaScript.h"
#include "getFreeVars.h"
#include "getBoundedVars.h"
#include "substitute.h"
#include "rename.h"
#include "evaluateEagerly.h"
#include "evaluateLazily.h"
#include "isCombinator.h"

class term;

/*
	This class hides implementation details of all actions,
	so that they don't have to (but can) be done directly.
	Only purpose is safer and more comfortable usage of
	all actions.
*/


class actions
{
public:
	static std::string printDeBruijn(term * t)
	{
		::printDeBruijn pdb;
		return pdb.perform(t);
	}	

	static std::string printFormally(term * t)
	{
		::printFormally pf;
		return pf.perform(t);
	}	

	static term * toCombinatorialTerm(term * t)
	{
		::toCombinatorialTerm tct;
		return tct.perform(t);
	}	

	static std::string printJavaScript(term * t)
	{
		::printJavaScript pjs;
		return pjs.perform(t);
	}	

	static std::set<std::string> getFreeVars(term * t)
	{
		::getFreeVars gfv;
		return gfv.perform(t);
	}	

	static std::set<std::string> getBoundedVars(term * t)
	{
		::getBoundedVars gbv;
		return gbv.perform(t);
	}	

	static term * substitute(term * t, var * from, term * to)
	{
		::substitute sub;
		return sub.perform(t, from, to);
	}	

	static void rename(term * t, std::string from, std::string on)
	{
		tmpNamespace::rename ren;
		return ren.perform(t, from, on);
	}	

	static term * evaluateEagerly(term * t, bool & limitExceeded, bool stopAtLambda, int limit)
	{
		::evaluateEagerly ee;
		return ee.perform(t, limitExceeded, stopAtLambda, limit);
	}	

	static term * evaluateLazily(term * t, bool & limitExceeded, bool stopAtLambda, int limit)
	{
		::evaluateLazily el;
		return el.perform(t, limitExceeded, stopAtLambda, limit);
	}	

	static bool isCombinator(term * t)
	{
		::isCombinator ic;
		return ic.perform(t);
	}	
};

#endif

