#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef BASE
#define BASE

int Random(int a, int b)
{
	srand((unsigned)time(NULL));
	return rand() % (b - a) + a;
}

#endif // !BASE


