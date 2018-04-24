#pragma once
#include "..\base.h"
#include "13_红黑树.h"

void test()
{
	RBTree *tree=NULL;
	RBInsert(&tree,19);

	RBInsert(&tree,3);
	InOrder(tree);
	printf("\n");

	RBInsert(&tree,5);
	InOrder(tree);
	printf("\n");


	RBInsert(&tree,6);
	InOrder(tree);
	printf("\n");
	
	int i;
	for(i=1;i<20;i++)
	{
		RBInsert(&tree,i);
		if(i%5==0)
			InOrder(tree);
		printf("\n");
	}
}
