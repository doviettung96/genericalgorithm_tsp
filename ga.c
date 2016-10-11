#include "ga.h"

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
		sub_x = t.city[i].add_x - t.city[i + 1].add_x;
		sub_y = t.city[i].add_y - t.city[i + 1].add_y;
		if (i == MAXCITY - 1)
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
	srand(time(NULL));
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

tour thebestTour(tour *t)
{
	int i;
	tour temp[MAXTOUR];
	for(i = 0; i < MAXTOUR; ++i)
		temp[i] = t[i];
	qsort(temp, MAXTOUR, sizeof(tour), compareFitness); //compareFitness is function to compare t[i] and t[j]
	return temp[0];
}

tour *iniPopulation()
{
	int j = 0;
	int swap_a, swap_b;
	int numberofSwap; //how many times to swap
	tour *newPopulation;
	newPopulation = (tour *)malloc(sizeof(tour) * MAXTOUR);
	if (newPopulation == NULL)
		exit(1);
	newPopulation[0] = iniTour();
	srand(time(NULL));
	for (int i = 1; i < MAXTOUR; ++i)
	{
		newPopulation[i] = newPopulation[0];
		while (compareTours(newPopulation, i) == 0)
		{
			numberofSwap = rand() % 40 + 10;
			for (j = 0; j < numberofSwap; ++j)
			{
				swap_a = rand() % MAXCITY;
				while (swap_a == swap_b)
					swap_b = rand() % MAXCITY;
				swap(&newPopulation[i].city[swap_a], &newPopulation[i].city[swap_b]);
			}
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
	return child;
}

tour mutation(tour child)
{
	int j;
	tour newChild = child;
	int swap_a, swap_b;
	int numberofSwap; //how many times to swap
	srand(time(NULL));
	numberofSwap = rand() % 20 + 10;
	for (j = 0; j < numberofSwap; ++j)
	{
		swap_a = rand() % MAXCITY;
		swap_b = rand() % MAXCITY;
		if (swap_a != swap_b)
			swap(&newChild.city[swap_a], &newChild.city[swap_b]);
	}
	return newChild;
}

void overWrite(tour *oldTour, tour *newTour)
{
	tour bestofOld = thebestTour(oldTour);
	int beOverWriten; //the tour that will be replace by the best of newTour
	beOverWriten = rand() % MAXTOUR;
	newTour[beOverWriten] = bestofOld;// check later...
	oldTour = newTour;
}

void showTour(tour t)
{
	int i;
	for (i = 0; i < MAXCITY; ++i)
	{
		// printf("%d-(%d;%d) ", t.city[i].number, t.city[i].add_x, t.city[i].add_y);
		//This is full form
		printf("%d ", t.city[i].number);
		//This is simple form
	}
	printf("\nDistance: %.2f\n", t.distance);
}

void showPopulation(tour *t)
{
	int i;
	for (i = 0; i < MAXTOUR; ++i)
	{
		printf("Tour %d-th\n", i + 1);
		showTour(t[i]);
	}
}


void dropPopulation(tour *t)
{
	if (t != NULL)
		free(t);
}
