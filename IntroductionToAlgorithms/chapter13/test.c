#include "13_红黑树.h"


int main()
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




	return 0;
}
