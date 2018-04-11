#include "12_BST.h"

int main()
{
	int a[10]={15,6,18,3,13,17,20,2,4,7};
	BSTree *root =BuildTree(NULL,a,0,10);
	InorderTreeWalk(root);
	printf("\n");

	InorderNoRecursion(root);

	return 0;

}
