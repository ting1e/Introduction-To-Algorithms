#include "12_1_建立_2_查询BST.h"

void TreeInsert(BSTree **root,int z)
{
	BSTree *x=*root;
	BSTree *y=NULL;
	while(x!=NULL)
	{
		y=x;
		if(x->key<=z)
		{
			x=x->left;
		}
		else
		{
			x=x->right;
		}
	}
	
	BSTree *node=(BSTree *)malloc(sizeof(BSTree));
	node->key=z;
	node->left=NULL;
	node->right=NULL;
	if(y==NULL)
	{
		node->p=NULL;
		*root=node;
	}
	else if(z<y->key)
	{
		node->p=y;
		y->left=node;
	}
	else
	{
		node->p=y;
		y->right=node;
	}
		
}
