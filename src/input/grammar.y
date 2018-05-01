%start line

%union
{
	term * t;
	std::vector<var *> * v;
};

%token CHAR EOLN LAMBDA DOT
		 LEFT_PARENTHESE RIGHT_PARENTHESE LEFT_BRACKET RIGHT_BRACKET
		 EQUAL NUMBER ADDITION MULTIPLICATION SUBTRACTION
		 TRUE FALSE OR AND NEG LESS_OR_EQUAL IS_ZERO
%type<t> line term termBraced var lambdaTerm application
%type<v> varList varListEmpty

%%

line:
	term EOLN {
		$$ = $1;
		result = $1;
	}
;

term:
	var { $$ = $1; }
	| lambdaTerm { $$ = $1; }
	| application { $$ = $1; }
	| termBraced { $$ = $1; }
	| LEFT_PARENTHESE term RIGHT_PARENTHESE LEFT_BRACKET var EQUAL term RIGHT_BRACKET
		{
			$$ = actions::substitute( $2, (var *) $5, $7 );
			delete $2;
			delete $5;
			delete $7;
		}
	| NUMBER { $$ = churchNumeral::makeTerm(d_scanner->tokenValue()); }
	| ADDITION { $$ = churchNumeral::makeAddition(); }
	| MULTIPLICATION { $$ = churchNumeral::makeMultiplication(); }
	| SUBTRACTION { $$ = churchNumeral::makeSubtraction(); }
	| TRUE { $$ = churchBooleans::makeTrue(); }
	| FALSE { $$ = churchBooleans::makeFalse(); }
	| OR { $$ = churchBooleans::makeOr(); }
	| AND { $$ = churchBooleans::makeAnd(); }
	| NEG { $$ = churchBooleans::makeNeg(); }
	| LESS_OR_EQUAL { $$ = churchNumeral::isLessOrEqual(); }
	| IS_ZERO { $$ = churchNumeral::isZero(); }
;

termBraced:
	LEFT_PARENTHESE term RIGHT_PARENTHESE { $$ = $2; }
;

var: CHAR  { $$ = new var((char) d_scanner->tokenValue()); }
;

varList:
	varListEmpty var { $1->push_back((var *)$2); $$ = $1; }
;

varListEmpty:
	/* empty */ { $$ = new std::vector<var *>(); }
	| varListEmpty var { $1->push_back((var *)$2); $$ = $1; }
;

lambdaTerm:
	LAMBDA varList DOT term
		{
			lambdaTerm * lt = new lambdaTerm( $2->back(), $4 );
			$2->pop_back();
			while( ! $2->empty() )
			{
				lt = new lambdaTerm($2->back(), lt);
				$2->pop_back();
			}
			delete $2;
			$$ = lt;
		}
;

application: 
	var var { $$ = new application($1,$2); }
	| var termBraced { $$ = new application($1,$2); }
	| termBraced var { $$ = new application($1,$2); }
	| termBraced termBraced { $$ = new application($1,$2); }
	| application var  { $$ = new application($1,$2); }
	| application termBraced { $$ = new application($1,$2); }
;

