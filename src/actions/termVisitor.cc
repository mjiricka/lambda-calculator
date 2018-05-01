#include "termVisitor.h"

#include "../term/term.h"
#include "../term/application.h"
#include "../term/lambdaTerm.h"
#include "../term/var.h"


void termVisitor::visit(term * t)
{
	if( application * a = dynamic_cast<application *>(t) )
	{
		this->visitApplication(a);
	}
	else if( lambdaTerm * lt = dynamic_cast<lambdaTerm *>(t) )
	{
		this->visitLambdaTerm(lt);
	}
	else if( var * v = dynamic_cast<var *>(t) )
	{
		this->visitVar(v);
	}
}

