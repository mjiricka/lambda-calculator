#include "lambdaTerm.h"
#include "var.h"
#include "../actions/termVisitor.h"

lambdaTerm::lambdaTerm(var * v, term * t)
	: _v(v), _t(t)
{ }

lambdaTerm::~lambdaTerm()
{
	delete _v;
	delete _t;
}

term * lambdaTerm::clone()
{
	return new lambdaTerm( (var *) v()->clone(), t()->clone() );
}

void lambdaTerm::accept(termVisitor * v)
{
	v->visitLambdaTerm(this);
}

var * lambdaTerm::v() { return _v; }

term * lambdaTerm::t() { return _t; }

void lambdaTerm::set_v(var * v)
{
	this->_v = v;
}

void lambdaTerm::set_t(term * t)
{
	this->_t = t;
}

