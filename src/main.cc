#include <iostream>
#include <string>
#include <readline/readline.h>
#include <readline/history.h>

#include "input/__parser.h"
#include "actions/actions.h"
#include "actions/churchNumeral.h"


int main()
{
	Parser p;
	std::string input;

	rl_bind_key('\t', rl_abort);	//disable readline auto-complete

	while( (input = readline("\n? ")).c_str() != NULL )
	{
		// Quit
		if( input == "quit" || input == "q" )
		{
			std::cout << "Bye!" << std::endl;
			return 0;
		}
		else {
			if( input[0] != 0 ) 
			{
				add_history(input.c_str());	// Add into cmd history.
				if( input[0] == '#' ) continue; // Skip comments.
			}
		}

		if( term * t = p.parse(input+"\n") )
		{
			// Print input 
			std::cout << "input: " << actions::printFormally(t) << std::endl;
			std::cout << "input (de Bruijn): " << actions::printDeBruijn(t) << std::endl;
			std::cout << "input (comb.term): ";
			term * combTerm = actions::toCombinatorialTerm(t);
			std::cout << actions::printFormally(combTerm) << std::endl;
			delete combTerm;

			// Print free variables
			std::set<std::string> freeVars = actions::getFreeVars(t);
			std::cout << "free vars: ";
			if( freeVars.empty() ) std::cout << "(none)";			
			std::set<std::string>::iterator it;
			for( it = freeVars.begin(); it != freeVars.end(); ++it )
				std::cout << *it << ' ';

			std::cout << std::endl;

			// Print bounded
			std::set<std::string> boundedVars = actions::getBoundedVars(t);
			std::cout << "bounded vars: ";
			if( boundedVars.empty() ) std::cout << "(none)";			
			for( it = boundedVars.begin(); it != boundedVars.end(); ++it )
				std::cout << *it << ' ';

			std::cout << std::endl;

			// Eager evaluation
			std::cout << "eager eval: ";
			bool leE;
			term * eagerEval = actions::evaluateEagerly(t, leE, true, 10000);
			std::cout << actions::printFormally(eagerEval); 
			if( leE ) std::cout << " !not evaluated completely!";
			else
			{
				// try to simplify
				term * tmp = actions::evaluateEagerly(eagerEval, leE, false, 7500);
				if( !leE )
				{
					delete eagerEval;
					eagerEval = tmp;
				}
			}
			std::cout << std::endl; 
			int leEi = churchNumeral::toInt(eagerEval);
			if( leEi != -1 )
				std::cout << "   (Church numeral: " << leEi << ")"  << std::endl;
			delete eagerEval;

			// Lazily evaluation
			std::cout << "lazy eval: ";
			bool leB;
			term * lazilyEval = actions::evaluateLazily(t, leB, true, 10000);
			std::cout << actions::printFormally(lazilyEval);
			if( leB ) std::cout << " !not evaluated completely!";
			else
			{
				// try to simplify
				term * tmp = actions::evaluateLazily(lazilyEval, leB, false, 7500);
				if( !leB )
				{
					delete lazilyEval;
					lazilyEval = tmp;
				}
			}
			std::cout << std::endl; 
			int leBi = churchNumeral::toInt(lazilyEval);
			if( leBi != -1 )
				std::cout << "   (Church numeral: " << leBi << ")"  << std::endl;
			delete lazilyEval;

			// Is combinator
			std::cout << "is combinator: ";
			bool isCombinator = actions::isCombinator(t);
			if( isCombinator )
				std::cout << "yes" << std::endl;
			else
				std::cout << "no" << std::endl;
			

			// Prints JavaScript code if possible
			if( isCombinator )
			{
				// print JavaScript code
				std::cout << "JavaScript:" << std::endl;
				std::cout << actions::printJavaScript(t);
			}


			delete t;
		}
		std::cout << std::endl;

	}

	return 0;
}

