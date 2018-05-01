#ifndef __TERM_H_
#define __TERM_H_

class termVisitor;

class term
{
public:
	virtual ~term();
	virtual term * clone() = 0;
	
	virtual void accept(termVisitor * v) = 0;
};


inline term::~term()
{ /* nothing */ } 

#endif
