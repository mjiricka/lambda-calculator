#include "churchBooleans.h"

#include "../term/application.h"
#include "../term/lambdaTerm.h"
#include "../term/var.h"


term * churchBooleans::makeTrue()
{
	return
		new lambdaTerm(
			new var('x'),
			new lambdaTerm(
				new var('y'),
				new var('x')
			)
		);
}

term * churchBooleans::makeFalse()
{
	return
		new lambdaTerm(
			new var('x'),
			new lambdaTerm(
				new var('y'),
				new var('y')
			)
		);
}

term * churchBooleans::makeAnd()
{
	return
		new lambdaTerm(
			new var('x'),
			new lambdaTerm(
				new var('y'),
				new application(
					new application(
						new var('x'),
						new var('y')
					),
					churchBooleans::makeFalse()
				)
			)
		);
}

term * churchBooleans::makeOr()
{
	return
		new lambdaTerm(
			new var('x'),
			new lambdaTerm(
				new var('y'),
				new application(
					new application(
						new var('x'),
						churchBooleans::makeTrue()
					),
					new var('y')
				)
			)
		);
}

term * churchBooleans::makeNeg()
{
	return
		new lambdaTerm(
			new var('x'),
			new application(
				new application(
					new var('x'),
					churchBooleans::makeFalse()
				),
				churchBooleans::makeTrue()
			)
		);
}

