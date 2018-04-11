#inlcude "..//base.h"



typedef struct BINARYSEARCHTREE
{
	int key;
	struct BINARYSEARCHTREE *left;
	struct BINARYSEARCHTREE *rigth;
	struct BINARYSEARCHTREE *p;
}BSTree;


BSTree* CreateBST(BSTree *parent, int x)
{
	BSTree *tree = (BSTree *)malloc(sizeof(BSTree));
	tree->p=parent;
	tree->right=NULL;
	tree->left=NULL;
	tree->key=x;
	return tree;
}


BSTree *BuildTree(BSTree *parent, int a[],int i,int size)
{
	BSTree *head=NULL;
	if(i<size)
	{
		head =(BSTree *)malloc(sizeof(BSTree));
		head->p=parent;
		head->rigth=NULL;
		head->left=NULL;
		head->key=a[i];




	}
}


