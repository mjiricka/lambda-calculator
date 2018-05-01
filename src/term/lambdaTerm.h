#ifndef __LAMBDA_TERM_H_
#define __LAMBDA_TERM_H_

#include "term.h"

class termVisitor;
class var;


class lambdaTerm : public term
{
public:
	lambdaTerm(var * v, term * t);
	~lambdaTerm();
	term * clone();
	
	void accept(termVisitor * v);
	
	var * v();
	term * t();

	void set_v(var * v);
	void set_t(term * t);

private:
	var * _v;
	term * _t;
};

#endif
