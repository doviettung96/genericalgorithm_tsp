#include "ga.h"

void showTour(tour t)
{
	int i;
	for (i = 0; i < MAXCITY; ++i)
		printf("%d ", t.city[i].number);
	printf("\nFitness: %.2f\n", t.distance);
}

void showPopulation(tour *t)
{
	int i;
	if (t == NULL)
	{
		printf("Empty population\n");
		exit(1);
	}
	else
	{
		for (i = 0; i < MAXTOUR; ++i)
		{
			printf("The %d-th tour\n", i + 1);
			showTour(t[i]);
		}
	}
}

int compareFitness(void const *a, void const *b)
{
	tour m, n;
	m = *((tour *)a);
	n = *((tour *)b);
	if (m.distance == n.distance)
		return 0;
	else if (m.distance > n.distance)
		return 1;
	else
		return -1;
}

int compareCity(city a, city b)
{
	if (a.number == b.number || a.add_x == b.add_x || a.add_y == b.add_y)
		return 1; //they are equal
	else
		return 0; //different
}

//total distance of the series of cities
float calculateFitness(tour t)
{
	int i = 0;
	float distance = 0;
	int sub_x, sub_y; //subtraction between x1, x2...
	for (i = 0; i < MAXCITY; ++i)
	{
		if (i != MAXCITY - 1)
		{
			sub_x = t.city[i + 1].add_x - t.city[i].add_x;
			sub_y = t.city[i + 1].add_y - t.city[i].add_y;
		}

		else
		{
			sub_x = t.city[i].add_x - t.city[0].add_x;
			sub_y = t.city[i].add_y - t.city[0].add_y;
		}
		distance += fabs(sqrt(sub_x * sub_x + sub_y * sub_y));
	}
	return distance;
}

tour iniTour() {
	tour t;
	for (int i = 0; i < MAXCITY; ++i)
	{
		t.city[i].number = i;
		t.city[i].add_x = rand() % 1000;
		t.city[i].add_y = rand() % 1000;
	}
	t.distance = calculateFitness(t);
	return t;
}

int compareTours(tour *t, int k)
{
	int i, j;
	int cityCompare, tourCompare; // 0 or 1 for each type of compare
	tour chosenTour = t[k]; //k-th tour
	tour interateTour; //for interation
	for (i = 0; i < k; ++i)
	{
		interateTour = t[i];
		cityCompare = 0;
		tourCompare = 1;
		for (j = 0; j < MAXCITY; ++j)
		{
			if (compareCity(interateTour.city[j], chosenTour.city[j]) == 0)
				// if (interateTour.city[j] != chosenTour.city[j])
				cityCompare = 1;
		}
		if (cityCompare * tourCompare == 0)
			return 0; //return 0 if they are the same
	}
	return 1; //return 1 if they are different
}

void swap(city *a, city *b)
{
	city temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void sortTour(tour *t)
{
	qsort(t, MAXTOUR, sizeof(tour), compareFitness);
}

tour thebestTour(tour *t)
{
	int i;
	tour temp[MAXTOUR];
	for (i = 0; i < MAXTOUR; ++i)
		temp[i] = t[i];
	qsort(temp, MAXTOUR, sizeof(tour), compareFitness); //compareFitness is function to compare t[i] and t[j]
	return temp[0];
}

tour inputfromFile(char fileName[])
{
	int i;
	FILE *fin;
	tour firstTour;
	int number, add_x, add_y;
	fin = fopen(fileName, "r");
	for (i = 0; i < MAXCITY; ++i)
	{
		fscanf(fin, "%d %d %d\n", &number, &add_x, &add_y);
		firstTour.city[i].number = number;
		firstTour.city[i].add_x = add_x;
		firstTour.city[i].add_y = add_y;
	}
	firstTour.distance = calculateFitness(firstTour);
	printf("Read success\n");
	fclose(fin);
	return firstTour;
}

tour *iniPopulation(tour firstTour)
{
	int j = 0;
	int swap_a, swap_b;
	int numberofSwap; //how many times to swap
	tour *newPopulation;
	newPopulation = (tour *)malloc(sizeof(tour) * MAXTOUR);
	if (newPopulation == NULL)
		exit(1);

	newPopulation[0] = firstTour;
	// showTour(firstTour);
	// srand(1);
	//maybe we will need srand(1) to keep the original population the same
	for (int i = 1; i < MAXTOUR; ++i)
	{
		newPopulation[i] = newPopulation[0];
		while (compareTours(newPopulation, i) == 0)
		{
			numberofSwap = rand() % (MAXCITY - 10) + 10;
			for (j = 0; j < numberofSwap; ++j)
			{
				swap_a = rand() % MAXCITY;
				//previously the while(swap_a == swap_b) makes it core dumpted
				swap_b = rand() % MAXCITY;
				swap(&newPopulation[i].city[swap_a], &newPopulation[i].city[swap_b]);
			}
			// printf("Numswap %d swap_a %d swap_b %d\n", numberofSwap, swap_a, swap_b);
			newPopulation[i].distance = calculateFitness(newPopulation[i]);
		}
	}
	return newPopulation;
}


tour crossover(tour a, tour b, int left, int right)
{
	int i, j;
	city x;
	tour child;
	int k;
	for (i = 0; i < MAXCITY; ++i)
	{
		if (i >= left && i <= right)
			child.city[i] = b.city[i];
		else
		{
			x = a.city[i];

			for (k = 0; k <= right - left; ++k)
			{
				for (j = left; j <= right; ++j)
					if (x.number == b.city[j].number)
						x = a.city[j];
			}
			child.city[i] = x;
		}
	}
	child.distance = calculateFitness(child);
	return child;
}

void mutation(tour *child)
{
	int j;
	int swap_a, swap_b;
	int numberofSwap; //how many times to swap
	numberofSwap = rand() % 20 + 10;
	for (j = 0; j < numberofSwap; ++j)
	{
		swap_a = rand() % MAXCITY;
		swap_b = rand() % MAXCITY;
		if (swap_a != swap_b)
			swap(&(*child).city[swap_a], &(*child).city[swap_b]);
	}
	(*child).distance = calculateFitness(*child);
}

void overWrite(tour *oldTour, tour *newTour)
{
	int i, j;
	tour bestofOld = thebestTour(oldTour);
	sortTour(newTour);
	newTour[MAXTOUR - 1] = bestofOld;
	for (i = 0; i < MAXTOUR; ++i)
	{
		for (j = 0; j < MAXCITY; ++j)
		{
			oldTour[i].city[j].number = newTour[i].city[j].number;
			oldTour[i].city[j].add_x = newTour[i].city[j].add_x;
			oldTour[i].city[j].add_y = newTour[i].city[j].add_y;
		}
		oldTour[i].distance = calculateFitness(newTour[i]);
	}
}

void exportResult(tour newTour, char fileIn[], char bestTemp[], char fileOut[], char currentTime[], int GENERATIONNUMBER, int seed)
{
	int i;
	FILE *fin, *fout;
	float lastbestFitness = 0.0;
	fin = fopen(bestTemp, "r");
	fscanf(fin, "%f\n", &lastbestFitness);
	fclose(fin);

	if (lastbestFitness == 0.0 || newTour.distance < lastbestFitness)
	{

		fin = fopen(bestTemp, "w");
		fout = fopen(fileOut, "w");

		fprintf(fout, "fileName: %s_evaluate(%d)_popSize(%d)_seed(%d)_Final.tour\n", fileIn, GENERATIONNUMBER, MAXTOUR, seed);
		fprintf(fout, "Seed: %d\n", seed);
		fprintf(fout, "Fitness: %.2f\n", newTour.distance);
		for (i = 0; i < MAXCITY; ++i)
			fprintf(fout, "%d ", newTour.city[i].number);
		fprintf(fout, "\nTime: %s\n", currentTime);
		fprintf(fin, "%.2f\n", newTour.distance);
		//writing to a temp file
		fprintf(fout, "\n");

		fclose(fin);
		fclose(fout);
	}

}

void dropPopulation(tour *t)
{
	if (t != NULL)
		free(t);
}