#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAXTOUR 100
#define RANDOMRANGE 100

typedef struct {
	int number;
	int add_x;
	int add_y;
} city;

int MAXCITY;

typedef struct {
	city city[1000]; //1 tour includes 50 cities
	float distance;
} tour;

void showTour(tour t);
void showPopulation(tour *t);
int compareFitness(void const *a, void const *b);
float calculateFitness(tour t);
 //calculate the total distance or result
// tour iniTour();
tour inputfromFile(char fileName[]);
int compareTours(tour *t, int k);
 //compare k-th tour with k - 1 previous tours
void swap(city *a, city *b);
void sortTour(tour *t);
tour thebestTour(tour *t);
tour *iniPopulation(tour firstTour);
// tour *iniPopulation(tour firstTour);
tour crossover(tour a, tour b, int left, int right);
 //after 1 child is born +1 to the countNumber
// void offSpring(tour *old, tour *child1, tour *child2);
void mutation(tour *child);

void overWrite(tour *oldTour, tour *newTour);
void exportReport(tour bestTour, char fileIn[], char fileOut[], int seed);
void exportResult(tour newTour, char fileIn[], char bestTemp[], char fileOut[], char currentTime[], int GENERATIONNUMBER, int seed);
void dropPopulation(tour *t);

//srand(seed) inside a function will fix the value regardless outside of it... while srand(seed) in main() will generate different values depending on seed