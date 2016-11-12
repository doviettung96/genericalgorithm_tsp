cnt=0 incre=1 instance="eil51.tsp" generationnumber=10000 crossoverconst=0.9 mutationconst=0.1 maxcity=51
while [ $cnt -lt 10 ]
do
	gcc -c tsp.c
	gcc -c ga.c
	gcc -o tsp tsp.o ga.o -lm
	./tsp $instance $generationnumber $crossoverconst $mutationconst $cnt $maxcity 
	sleep 5	
	cnt=`expr $cnt + 1`
done
