all: test
test: test.o ga.o
	gcc -o test test.o ga.o -lm
test.o: test.c
	gcc -c test.c
ga.o: ga.c
	gcc -c ga.c