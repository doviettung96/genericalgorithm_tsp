all: test tsp
test: test.o ga.o
	gcc -o test test.o ga.o -lm
tsp: tsp.o ga.o
	gcc -o tsp tsp.o ga.o -lm
tsp.o: tsp.c
	gcc -c tsp.c
test.o: test.c
	gcc -c test.c
ga.o: ga.c
	gcc -c ga.c