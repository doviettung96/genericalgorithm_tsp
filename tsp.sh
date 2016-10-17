cnt=1
while [ $cnt -lt 10 ]
do
	gcc -c tsp.c
	gcc -c ga.c
	gcc -o tsp tsp.o ga.o -lm
	./tsp $cnt  
	sleep 5	
	cnt=`expr $cnt + 1`
done
