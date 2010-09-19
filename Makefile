all : test

test : test.o
	g++ -Wall -Werror -g -o $@ $^

%.o : %.cpp
	g++ -Wall -Werror -g -O0 -c -o $@ $<


