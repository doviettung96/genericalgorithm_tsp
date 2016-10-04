#include "ga.h"

object *iniPopulation()
{
	object *newPopulation;
	newPopulation = (object *)malloc(sizeof(object));
	if(newPopulation == NULL)
		exit(1);
	return newPopulation;
}

void swapMutation(city *buf, int total, int i, int j)
{
	buf temp = buf[i];
	buf[i] = buf[j];
	buf[j] = temp;
}

int compare2Objects(object a, object b, int total)
{
	int i = 0;
	for(i = 0; i < total; ++i)
		if(a.city[i].number != b.city[i].number)
			return 1; //return 1 if they are different
	return 0; //return 0 if they are all same
}

void 
