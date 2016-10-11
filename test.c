#include "ga.h"
#include "menu.h"

#define MAXSECTION 5

void main()
{
	int left, right;
	int i;
	int choice;
	int parent1, parent2;
	tour *old, *new;
	tour child1, child2; //after crossover
	tour child3, child4;//after mutation
	int countNew = 0; //count the number of tour added to new
	int randomMutation, randomCrossover; //for mutation and crossover
	char sections[MAXSECTION][40] = {"Initialize population", "Show all the population", "Crossover and mutation", "Show the best result", "Exit"};

	srand(time(NULL));
	new = (tour *)malloc(sizeof(tour) * MAXTOUR);
	do {
		choice = getMenu(sections, MAXSECTION);
		switch (choice)
		{
		case 1:
			old = iniPopulation();
			break;
		case 2:
			showPopulation(old);
			break;
		case 3:
			for (i = 0; i < GENERATIONNUMBER; ++i)
			{
				for (countNew = 0; countNew < MAXTOUR;)
				{
					randomCrossover = rand() % RANDOMRANGE;
					if (randomCrossover < CROSSOVERCONST)
					{
						parent1 = rand() % MAXTOUR;
						parent2 = rand() % MAXTOUR;

						left = rand() % MAXCITY;
						right = rand() % MAXCITY;
						// printf("%d-%d %d-%d\n", parent1, parent2, left, right);
						//different for sure
						if (sizeof(new) == sizeof(tour) * MAXTOUR)
							overWrite(old, new);
						//if new is maximum so take the best of old then write to new and overwrite to old again
						child1 = crossover(old[parent1], old[parent2], left, right);
						child2 = crossover(old[parent2], old[parent1], left, right);
						new[countNew] = child1;
						++countNew;
						new[countNew] = child2;
						++countNew;
						// crossover;
						//Now add children into New...

						randomMutation = rand() % RANDOMRANGE;
						if (randomMutation < MUTATIONCONST)
						{
							if (sizeof(new) == sizeof(tour) * MAXTOUR)
								overWrite(old, new);
							//if new is maximum so take the best of old then write to new and overwrite to old again

							child3 = mutation(child1);
							new[countNew] = child3;
							++countNew;
							child4 = mutation(child2);
							new[countNew] = child4;
							++countNew;
						}
					}
				}
			}
			break;
		case 4:
			showTour(thebestTour(old));
			break;
		case MAXSECTION:
			dropPopulation(old);
			dropPopulation(new);
			//A dropPopulation or destroyPopulation function is need
			break;
		default: printf("Choice must be from 1 to %d", MAXSECTION);
			break;
		}
	} while (choice != MAXSECTION);
}