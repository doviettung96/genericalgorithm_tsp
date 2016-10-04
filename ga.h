#include "tsp.h"


typedef struct {
	city city[MAX]; //1 object includes 50 cities
} object;

object *iniPopulation();
void swapMutation(city *buf, int total, int i, int j);
int compare2Objects(object a, object b, int total);
