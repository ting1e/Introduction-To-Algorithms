
#ifndef BASE
#define BASE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE 50

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

int Random(int a, int b)
{
	srand((unsigned)time(NULL));
	return rand() % (b - a) + a;
}

#endif // !BASE


