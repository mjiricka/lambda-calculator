#ifndef __CHURCH_BOOLEANS_H__
#define __CHURCH_BOOLEANS_H__

class term;

class churchBooleans
{
public:
	static term * makeTrue();
	static term * makeFalse();
	static term * makeAnd();
	static term * makeOr();
	static term * makeNeg();
};

#endif
