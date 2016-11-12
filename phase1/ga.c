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

float calculateDistance(city a, city b)
{
	float sub_x, sub_y;
	float distance;
	sub_x = a.add_x - b.add_x;
	sub_y = a.add_y - b.add_y;
	distance = fabs(sqrt(sub_x * sub_x + sub_y * sub_y));
	return distance;
}

//total distance of the series of cities
float calculateFitness(tour t)
{
	int i = 0;
	float distance = 0;
	float sub_x, sub_y; //subtraction between x1, x2...
	for (i = 0; i < MAXCITY; ++i)
	{
		if (i != MAXCITY - 1)
			distance += calculateDistance(t.city[i + 1], t.city[i]);

		else
			distance += calculateDistance(t.city[i], t.city[0]);
	}
	return distance;
}

// tour iniTour() {
// 	tour t;
// 	for (int i = 0; i < MAXCITY; ++i)
// 	{
// 		t.city[i].number = i;
// 		t.city[i].add_x = rand() % 1000;
// 		t.city[i].add_y = rand() % 1000;
// 	}
// 	t.distance = calculateFitness(t);
// 	return t;
// }

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

void sortTour(tour *t, int max)
{
	qsort(t, max, sizeof(tour), compareFitness);
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
	int number;
	float add_x, add_y;
	fin = fopen(fileName, "r");
	char temp[100];

	while (1) {
		fgets(temp, 100, fin);
		// if(isdigit(temp[0]))
		// 	MAXCITY = atoi(temp);
		if (strcmp(temp, "NODE_COORD_SECTION\n") == 0)
			break;
	}

	// firstTour.city = (city *)malloc(sizeof(city) * MAXCITY);
	// printf("Input done!\n");
	for (i = 0; i < MAXCITY; ++i)
	{
		fscanf(fin, "%d %f %f\n", &number, &add_x, &add_y);
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

void findTemp(city *temp, tour parent, int left, int right)
{
	int i, position;

	for (i = 0; i < MAXCITY; ++i)
		if (compareCity(temp[0], parent.city[i]) == 1)
			position = i;

	if (position == 0)
	{
		temp[left] = parent.city[MAXCITY - 1];
		temp[right] = parent.city[1];
	}
	else if (position == MAXCITY - 1)
	{
		temp[left] = parent.city[MAXCITY - 2];
		temp[right] = parent.city[0];
	}
	else
	{
		temp[left] = parent.city[position - 1];
		temp[right] = parent.city[position + 1];
	}
}

int compareFloat(void const *m, void const *n)
{
	float a, b;
	a = *((float *)m);
	b = *((float *)n);
	if (a > b)
		return 1;
	else if (a < b)
		return -1;
	else
		return 0;
}

void minTemp(float distance[], int *index_min)
{
	int i;
	int j = 1;
	float tempDistance[5];
	tempDistance[0] = 0;
	index_min[0] = 0;
	for (i = 1; i < 5; ++i)
		tempDistance[i] = distance[i];

	qsort(tempDistance, 5, sizeof(float), compareFloat);

	for (i = 1; i < 5; ++i)
		for (j = 1; j < 5; ++j)
			if (tempDistance[i] == distance[j])
				index_min[i] = j;
	//find indexes of the smallest distances
}

tour MSCX(tour a, tour b)
{
	tour child;
	city temp[5];
	int position = -1;
	int count;
	int index_min[5];
	int i;
	float distance[5];
	temp[0] = a.city[0];
	child.city[0] = a.city[0];
	count = 1;
	distance[0] = 0;
	while (1)
	{
		findTemp(temp, a, 1, 2);
		findTemp(temp, b, 3, 4);
		for (i = 1; i < 5; ++i)
			distance[i] = calculateDistance(temp[0], temp[i]);

		minTemp(distance, index_min);

		for (i = 0; i < MAXCITY; ++i)
			if (compareCity(temp[index_min[1]], child.city[i]) == 1)
				position = i;
		if (position == -1)
			child.city[count++] = temp[index_min[1]];
		else
			child.city[count++] = temp[index_min[2]];
		temp[0] = child.city[count];
		if (count == MAXCITY)
			break;
	}
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

void copyData(tour *target, tour *source, int already_in_target, int max)
{
	int i, j;
	for (i = 0; i < max; ++i)
	{
		for (j = 0; j < MAXCITY; ++j)
		{
			target[i + already_in_target].city[j].number = source[i].city[j].number;
			target[i + already_in_target].city[j].add_x = source[i].city[j].add_x;
			target[i + already_in_target].city[j].add_y = source[i].city[j].add_y;
		}
		target[i + already_in_target].distance = calculateFitness(source[i]);
	}
}

void overWrite(tour *oldTour, tour *newTour)
{
	tour *temp;
	temp = (tour *)malloc(sizeof(tour) * MAXTOUR * 2);
	copyData(temp, newTour, 0, MAXTOUR);
	copyData(temp, oldTour, MAXTOUR, MAXTOUR);
	sortTour(temp, MAXTOUR * 2);
	copyData(oldTour, temp, 0, MAXTOUR);
	free(temp);
}

void regenerationPop(tour *oldTour)
{
	int j = 0;
	int swap_a, swap_b;
	int numberofSwap; //how many times to swap
	tour *newPopulation;
	newPopulation = (tour *)malloc(sizeof(tour) * MAXTOUR);
	sortTour(oldTour, MAXTOUR);
	copyData(newPopulation, oldTour, 0, 50);

	// showTour(firstTour);
	// srand(1);
	//maybe we will need srand(1) to keep the original population the same
	for (int i = 50; i < MAXTOUR; ++i)
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
	copyData(oldTour, newPopulation, 0, MAXTOUR);
	free(newPopulation);
}

void exportReport(tour bestTour, char fileIn[], char fileOut[], int seed)
{
	FILE *f;
	f = fopen(fileOut, "a");
	fprintf(f, "File: %s - Seed %d: \n%.2f\n", fileIn, seed, bestTour.distance);
	fclose(f);
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