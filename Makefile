.PHONY: all

all: lambdacalc
	
lambdacalc: src/*.cc src/*/*.cc src/*/*.h src/input/grammar.y src/input/my_parser.h~
	cp src/input/my_parser.h~ src/input/__parser.h
	cd src/input/; bisonc++ -Hpreinclude.h -f__parser -p__parse.cc -sscanner.h -l grammar.y
	g++ -g -O -Wall -Wextra -o lambdacalc src/*.cc src/*/*.cc -lreadline

clean:
	rm -f lambdacalc
	rm -f src/input/__* 

debug-grammar:
	cd src/input/; bisonc++ -A --debug --construction  -Hpreinclude.h -f__parser -p__parse.cc -sscanner.h -l grammar.y
	vim src/input/grammar.y.output
	rm src/input/grammar.y.output
	
examples: all
	./lambdacalc < sample_input > sample_output
	./lambdacalc < sample_input2 > sample_output2
	./lambdacalc < sample_input3 > sample_output3
	m4 sample_input4.m4 > sample_input4
	./lambdacalc < sample_input4 > sample_output4

