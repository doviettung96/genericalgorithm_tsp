#include <stdio.h>

int getMenu(char sections[][40], int maxsection) {
	int choice;
	printf("\n");
	for (int i = 0; i < maxsection; ++i)
		printf("%2d. %s\n", i + 1, sections[i]);
	printf("Your choice: ");
	scanf("%d", &choice);
	printf("\n");
	return choice;
}