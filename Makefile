.PHONY: all grammar debug-grammar

all: lambdacalc
	
lambdacalc: src/*.cc src/*/*.cc src/*/*.h
	mkdir -p build
	g++ -g -O -Wall -Wextra -o build/lambdacalc src/*.cc src/*/*.cc -lreadline

clean:
	rm -rf build/

grammar:
	rm -f src/input/__* 
	cp src/input/my_parser.h~ src/input/__parser.h
	cd src/input/; bisonc++ -Hpreinclude.h -f__parser -p__parse.cc -sscanner.h -l grammar.y

debug-grammar:
	cd src/input/; bisonc++ -A --debug --construction  -Hpreinclude.h -f__parser -p__parse.cc -sscanner.h -l grammar.y
	vim src/input/grammar.y.output
	rm src/input/grammar.y.output

