#include "churchNumeral.h"

#include <string>
#include <iostream>
#include "actions.h"
#include "../term/application.h"
#include "../term/lambdaTerm.h"
#include "../term/var.h"
#include "../input/__parser.h"
#include "churchBooleans.h"


int churchNumeral::toInt( term * t )
{
	std::string s = actions::printDeBruijn(t);
	
	if( s == "\\.(\\.(0))" ) return 0;

	if( s.substr(0,5) != "\\.(\\." ) return -1;
	
	size_t i = 5;
	size_t n = 0;

	while( i < s.length() )
	{
		std::string ss = s.substr(i,2);
		
		if( ss != "(1" )
		{
			if( ss == "0)" && (s.length()-(1+(i+1)) == n) )
				return (int) n;
			else
				return -1;
		}

		i += 2;
		++n;
	}

	return (int) n;
}

term * churchNumeral::makeTerm( int n )
{
	var * x = new var('x');
	var * f = new var('f');

	term * t = x->clone();
	for( int i = 0; i < n; ++i )
		t = new application(f->clone(), t);

	lambdaTerm * start
		= new lambdaTerm(
			(var *) f->clone(),
			new lambdaTerm((var *) x->clone(), t)
		);

	delete x;
	delete f;

	return start;
}

term * churchNumeral::makeAddition()
{
	return
		new lambdaTerm(
			new var('m'),
			new lambdaTerm(
				new var('n'),
				new lambdaTerm(
					new var('f'),
					new lambdaTerm(
						new var('x'),
						new application(
							new application(
								new var('m'),
								new var('f')
							),
							new application(
								new application(
									new var('n'),
									new var('f')
								),
								new var('x')
							)							
						)
					)
				)
			)
		);
}

term * churchNumeral::makeMultiplication()
{
	return
		new lambdaTerm(
			new var('m'),
			new lambdaTerm(
				new var('n'),
				new lambdaTerm(
					new var('f'),
					new application(
						new var('m'),
						new application( new var('n'), new var('f'))
					)
				)
			)
		);
}

term * churchNumeral::makeSubtraction()
{
	term * t1 =
		new lambdaTerm(
			new var('g'),
			new lambdaTerm(
				new var('h'),
				new application(
					new var('h'),
					new application(
						new var('g'),
						new var('f')
					)
				)
			)
		);

	term * t2 =
		new lambdaTerm(
			new var('u'),
			new var('x')
		);

	term * t3 =
		new lambdaTerm(
			new var('u'),
			new var('u')
		);

	term * predecessor =
		new lambdaTerm(
			new var('n'),
			new lambdaTerm(
				new var('f'),
				new lambdaTerm(
					new var('x'),
					new application(
						new application(
							new application(
								new var('n'),
								t1
							),
							t2
						),
						t3
					)
				)
			)
		);

	term * subtraction =
		new lambdaTerm(
			new var('m'),
			new lambdaTerm(
				new var('n'),
				new application(
					new application(
						new  var('n'),
						predecessor
					),
					new var('m')
				)
			)
		);

	return subtraction;
}

term * churchNumeral::isZero()
{
	return
		new lambdaTerm(
			new var('m'),
			new application(
				new application(
					new var('m'),
					new lambdaTerm(
						new var('x'),
						churchBooleans::makeFalse()
					)
				),
				churchBooleans::makeTrue()
			)
		);					
}

term * churchNumeral::isLessOrEqual()
{
	return
		new lambdaTerm(
			new var('m'),
			new lambdaTerm(
				new var('n'),
					new application(
						churchNumeral::isZero(),
						new application(
							new application(
								churchNumeral::makeSubtraction(),
								new var('m')
							),
							new var('n')
						)
					)
				)
			);
}

