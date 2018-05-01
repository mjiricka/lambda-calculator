#ifndef __CHURCH_NUMERAL_H__
#define __CHURCH_NUMERAL_H__

class term;


class churchNumeral
{
public:
	// Returns number that corresponds to Church numeral in term t,
	// -1 otherwise.
	static int toInt( term * t );
	static term * makeTerm( int n );
	static term * makeAddition();
	static term * makeMultiplication();
	static term * makeSubtraction();
	static term * isZero();
	static term * isLessOrEqual();
};

#endif
