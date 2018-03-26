
#ifndef BASE
#define BASE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int Random(int a, int b)
{
	srand((unsigned)time(NULL));
	return rand() % (b - a) + a;
}

#endif // !BASE


