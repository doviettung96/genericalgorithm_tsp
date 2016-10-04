#include "tsp.h"

//total distance of the series of cities
void totalDistance(city c[], int total)
{
	int i = 0;
	float distance = 0;
	float sub_x, sub_y; //subtraction between x1, x2...
	for (i = 0; i < total - 2; ++i)
	{
		sub_x = c[i].x - c[i + 1].x;
		sub_y = c[i].y - c[i + 1].y;
		distance += sqrt(sub_x * sub_x + sub_y * sub_y);
	}
	distance += sqrt((c[total - 2].x - c[0].x) * (c[total - 2].x - c[0].x) + (c[total - 2].y - c[0].y) * (c[total - 2].y - c[0].y)); //last - first
	c[total].distance = distance;
}

int floatCompare(void const *x, void const *y) {
	float m, n;
	m = *(float *)x;
	n = *(float *)y;
	if(m == n)
		return 0;
	else if(m > n)
		return 1;
	else
		return -1;
}

