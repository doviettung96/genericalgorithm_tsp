#include "ga.h"
#include <ctype.h>

#define MAXSECTION 6

void main(int argc, char **argv)
{
	int left, right;
	int i;
	int countSeed = atoi(argv[1]);
	int parent1, parent2;
	tour *old, *new;
	tour child1, child2; //after crossover
	tour child3, child4;//after mutation
	int countNew = 0; //count the number of tour added to new
	int randomMutation, randomCrossover; //for mutation and crossover


	new = (tour *)malloc(sizeof(tour) * MAXTOUR);

	old = iniPopulation(inputfromFile("eil51.tsp"));
	// printf("%d - %d\n", sizeof(old), sizeof(tour));

	// printf("Old population\n");
	// showPopulation(old);
	// // printf("%d ", sizeof(old));


	// printf("New population\n");
	// showPopulation(new);


	printf("Crossover\n");
	srand(time(NULL)); //begin of each choice should have srand...
	srand(countSeed);
	for (i = 0; i < GENERATIONNUMBER; ++i)
	{
		countNew = 0;
		while (countNew < MAXTOUR)
		{
			randomCrossover = rand() % RANDOMRANGE;
			if (randomCrossover < CROSSOVERCONST)
			{
				parent1 = rand() % MAXTOUR;
				parent2 = rand() % MAXTOUR;
				left = rand() % MAXCITY;
				right = left + rand() % (MAXCITY - left);
				// printf("%d %d %d %d\n", parent1, parent2, left, right);
				// printf("Error!\n");
				child1 = crossover(old[parent1], old[parent2], left, right);
				child2 = crossover(old[parent2], old[parent1], left, right);


				// crossover
				randomMutation = rand() % RANDOMRANGE;
				if (randomMutation < MUTATIONCONST)
				{
					mutation(&child1);
					mutation(&child2);
				}

				//maybe born only 2 children
				new[countNew++] = child1;
				new[countNew++] = child2;

				if (countNew == MAXTOUR)
					overWrite(old, new);
				//if new is maximum so take the best of old then write to new and overwrite to old again
				//Now add children into New.
			}
		}
	}
	
	printf("Count seed: %d\n", countSeed);

	printf("The best result of old\n");
	showTour(thebestTour(old));


	if (old != NULL)
		dropPopulation(old);
	if (new != NULL)
		dropPopulation(new);
	//A dropPopulation or destroyPopulation function is need


}