#include "application.h"

#include "../actions/termVisitor.h"

application::application(term * l, term * r)
	: _l(l), _r(r)
{ }

application::~application()
{
	delete _l;
	delete _r;
}

term * application::clone()
{
	return new application( l()->clone(), r()->clone() );
}

void application::accept(termVisitor * v)
{
	v->visitApplication(this);
}

term * application::l() { return _l; }

term * application::r() { return _r; }
	
void application::set_l(term * l)
{
	this->_l  = l;
}

void application::set_r(term * r)
{
	this->_r  = r;
}

