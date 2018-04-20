#include "15_1_钢条切割.h"

int main()
{
	int p[]={0,1,5,8,9,10,17,17,20,24,30};
	int pi;
	pi=CutRod(p,10);
	printf("10: price %d\n ",pi);

	pi=MemoizedCutRod(p,10);
	printf("10: price %d\n ",pi);
	
	pi=BottomUpRod(p,10);
	printf("10: price %d\n ",pi);


	PrintCutRodSolution(p,9);

	return 0;
}
