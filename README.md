# λ calculator

This is one of my school projects: [lambda calculus](https://en.wikipedia.org/wiki/Lambda_calculus) evaluator. It was made for Functional Programming course.
It helped me to grasp the topic better.



## What it can do

After launching the program user gets into an interactive prompt. Expected input is an 𝜆 term (or `q` or `quit` to quit program). The program responds
for each 𝜆 term input with some information about the term.

## Input

Foremost, any whitespace character is skipped.

### 𝜆 term

𝜆 term is:
 - variable: any lowercase alphabetic character; e.g. `a` or `b`;
 - lambda abstraction: slash `\`, then list of variables, dot `.` and then 𝜆 term; e.g. `\x.a`, `\xy.xbc`, `\x.\x.a`;
 - application: two consecutive 𝜆 terms, lambda abstractions must be enclosed within curly braces; e.g. `ab`, `a(\x.x)`, `(\x.x)(\y.y)`;
 - substitution: in this form: `(<𝜆 term>)[<variable>=<𝜆 term>]`, e.g. `(a)[b=c]`, `((a)[b=c])[a=\x.a]`.

### Church numerals

Numbers represent [Church numerals](https://en.wikipedia.org/wiki/Church_encoding#Church_numerals). E.g. `1` is `\f.(\x.(fx))`, `10` is `\f.(\x.(f(f(f(f(f(f(f(f(f(fx)))))))))))`.

Following operations with Church numerals are supported: addition `+`, subtraction `-` and multiplication `*`. Operations must be enclosed within curly braces. E.g. `(+)(1)(2)`.

### Church booleans

[Church booleans](https://en.wikipedia.org/wiki/Church_encoding#Church_Booleans) are also build in:
 - `T` is true;
 - `F` is false;
 - `A` is logical and;
 - `O` is logical or;
 - `N` is logical negation.

E.g. `(A)(T)(F)` prints `\x.(\y.(y))`, which is both Church numeral for zero and Church boolean for false. The same output will be for `(N)(T)`.

### Numerals comparison

There is one more operator for Church numerals comparison: `?`.

E.g. `(?)(1)` results again into Church boolean for false (`F`).


## Output

### input

Rewritten input so that all functions have single argument and all substitutions are performed, also all brackets are print. (I will call it *canonical* notation.)

E.g. for `\xyz.a` it is `\x.(\y.(\z.(a)))`. For `(\z.za)[a=x]` is canonical term `\z.(zx)`. Renaming is not performed, e.g. `(\z.z)[z=x]` is still `\z.(z)`.

### input in de Bruijn

Input in [de Bruijn index notation](https://en.wikipedia.org/wiki/De_Bruijn_index).

E.g. for `\x.((\x.xx)ab)` it is `\.(((\.(00))a)b)`.

### input as combinatorial term

[Combinatory calculus](https://en.wikipedia.org/wiki/Combinatory_logic#Combinatory_terms)
has some predefined terms: **I** (identity), **K** (constant) and **S** (application).
This should be term rewritten with these combinatorial term.

### free variables

List of all [free variables](https://en.wikipedia.org/wiki/Lambda_calculus#Free_variables) in the term.

### bound variables

List of all [bound variables](https://en.wikipedia.org/wiki/Lambda_calculus#Free_and_bound_variables) of the term.

### eager evaluation

Input is evaluated eagerly. Arguments are evaluated from left to right, output is in canonical notation.

E.g. `(\x.xy)(\a.a)` is evaluated to `y`. Term `(\x.y)((\x.xx)(\x.xx))` is evaluated to the same term, but with notice it was not evaluated completely.

If output is in form of Church numeral, it is also printed corresponding integer number.

### lazy evaluation

Input is evaluated lazily.

E.g. term `(\x.y)((\x.xx)(\x.xx))` is evaluated to `y`.

Same as in eager evaluation, if output is in form of Church numeral, it is also printed corresponding integer number.

### is combinator

Says whether term is [combinator](https://en.wikipedia.org/wiki/Lambda_calculus#Free_and_bound_variables).
Combinator is other name for *closed* term (term that has no free variables).

E.g. `\fx.fx` or `\f.(\x.f(xx))(\x.f(xx))` are combinators.
(The latter is [fixed point combinator](https://en.wikipedia.org/wiki/Fixed-point_combinator#Fixed_point_combinators_in_lambda_calculus)).

### JavaScript

I do not remember what this is. But when 𝜆 term is a combinator, its representation(?) in JavaScript is printed.



## How to build and run

Library `readline` and `g++` are needed for compilation.

This compiles the project:

    make

Then it can be started:

    cd build
    ./lambdacalc



## Notes

 - Original parser generated by `bison++` is committed. I tried to regenerate it with a newer version (`1.21.9-1`), but it would require changes in code to make it work.
     - Command `make grammar` regenerates it. (See `Makefile` for details.)
     - I made my own lexer, `yacc` was not used.
     - I also made some hack to resulted `bison` parser. I do not remember what it was, but that is why `my_parser.h~` exists.

