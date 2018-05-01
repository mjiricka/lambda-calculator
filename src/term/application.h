#ifndef __APPLICATION_H_
#define __APPLICATION_H_

#include "term.h"

class termVisitor;

class application : public term
{
public:
	application(term * l, term * r);
	~application();
	term * clone();

	void accept(termVisitor * v);

	term * l();
	term * r();

	void set_l(term * l);
	void set_r(term * r);

private:
	term * _l;
	term * _r;
};

#endif
