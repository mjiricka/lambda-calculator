#include "var.h"

#include <string>
#include "../actions/termVisitor.h"


var::var(std::string identifier)
	: _identifier(identifier)
{ }

var::var(char identifier)
{
	_identifier = identifier;
}

var::~var()
{ }

term * var::clone()
{
	return new var( identifier() );
}

void var::accept(termVisitor * v)
{
	v->visitVar(this);
}

std::string var::identifier()
{
	return _identifier;
}

void var::set_identifier(std::string newIdentifier)
{
	_identifier = newIdentifier;
}

