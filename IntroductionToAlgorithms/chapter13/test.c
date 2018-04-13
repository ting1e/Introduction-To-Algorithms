#include "13_红黑树.h"


int main()
{
	RBTree *tree=NULL;
	RBInsert(&tree,19);
	RBInsert(&tree,3);
	RBInsert(&tree,5);
	RBInsert(&tree,6);

	InOrder(tree);






	return 0;
}
