#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX 51

typedef struct {
	int number;
	float add_x;
	float add_y;
	float distance;
} city;

void totalDistance(city c[], int total); //calculate the total distance or result 
int floatCompare(void const *x, void const *y); //compare the distance

