#include "ga.h"

int compareFitness(tour a, tour b)
{
	if (a.distance == b.distance)
		return 0;
	else if (a.distance > b.distance)
		return 1;
	else
		return -1;
}

//total distance of the series of cities
void totalDistance(tour t)
{
	int i = 0;
	float distance = 0;
	int sub_x, sub_y; //subtraction between x1, x2...
	for (i = 0; i < MAXCITY - 1; ++i)
	{
		sub_x = t.city[i].add_x - t.city[i + 1].add_x;
		sub_y = t.city[i].add_y - t.city[i + 1].add_y;
		distance += sqrt(sub_x * sub_x + sub_y * sub_y);
	}
	distance += sqrt((t.city[MAXCITY - 1].add_x - t.city[0].add_x) * (t.city[MAXCITY - 1].add_x - t.city0].add_x) + (t.city[MAXCITY - 1].add_y - t.city[0].add_y) * (t.city[MAXCITY - 1].add_y - t.city[0].add_y)); //last - first
	t.distance = distance;
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
	t.distance = totalDistance(t);
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
			if (interateTour.city[j] != chosenTour.city[j])
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
	qsort(t, MAXTOUR, sizeof(tour), compareFitness); //compareFitness is function to compare t[i] and t[j]
	return t[0];
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
	t[0] = iniTour();
	srand(time(NULL));
	for (int i = 1; i < MAXTOUR; ++i)
	{
		t[i] = t[0];
		while (compareTour(t, i) == 0)
		{
			numberofSwap = rand() % 40 + 10;
			for (j = 0; j < numberofSwap; ++j)
			{
				swap_a = rand() % MAXCITY;
				while (swap_a == swap_b)
					swap_b = rand() % MAXCITY;
				swap(&t[i].city[swap_a], &t[i].city[swap_b]);
			}

		}
	}
	return newPopulation;
}

void crossover(tour a, tour b, tour *child, int left, int right)
{
	int i, j;
	city x;

	int k;
	for (i = 0; i < MAXCITY; ++i)
	{
		if (i >= left && i <= right)
			(*child).city[i] = b.city[i];
		else
		{
			x = a.city[i];

			for (k = 0; k <= right - left; ++k)
			{
				for (j = left; j <= right; ++j)
					if (x.number == b.city[j].number)
						x = a.city[j];
			}
			(*child).city[i] = x;
		}
	}
}

void mutation(tour child)
{
	int j;
	int swap_a, swap_b;
	int numberofSwap; //how many times to swap
	srand(time(NULL));
	numberofSwap = rand() % 20 + 10;
	for (j = 0; j < numberofSwap; ++j)
	{
		swap_a = rand() % MAXCITY;
		swap_b = rand() % MAXCITY;
		if (swap_a != swap_b)
			swap(&child.city[swap_a], &child.city[swap_b]);
	}
}

void overWrite(tour *oldTour, tour *newTour)
{
	tour bestofOld = thebestTour(oldTour);
	int beOverWriten; //the tour that will be replace by the best of newTour
	beOverWriten = rand() % MAXTOUR;
	newTour[beOverWriten] = bestofOld;// check later...
}