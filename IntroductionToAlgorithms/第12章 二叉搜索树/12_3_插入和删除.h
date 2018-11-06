#pragma once
#include "..\base.h"
#include "12_1_建立_2_查询BST.h"

void TreeInsert(BSTree **root,int z)
{
	BSTree *x=*root;
	BSTree *y=NULL;
	while(x!=NULL)
	{
		y=x;
		if(x->key>=z)
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


void Transplant(BSTree **root,BSTree *u,BSTree *v)
{
	if(u->p==NULL)
	{
		*root=v;
	}
	else if(u==u->p->left)
	{
		u->p->left=v;
	}
	else
	{
		u->p->right=v;
	}
	if(v!=NULL)
	{
		v->p=u->p;
	}
}

void TreeDelete(BSTree **root,int k)
{
	BSTree *z=IterativeTreeSearch(*root,k);
	if(z==NULL)
	{
		return;
	}

	if(z->left==NULL)
	{
		Transplant(root,z,z->right);
	}
	else if(z->right==NULL)
	{
		Transplant(root,z,z->left);
	}
	else
	{
		BSTree *y=TreeMinimum(z->right);
		if(y->p!=z)
		{
			Transplant(root,y,y->right);
			y->right=z->right;
			y->right->p=y;
		}
		Transplant(root,z,y);
		y->left=z->left;
		y->left->p=y;
	}
	free(z);
}

//练习 12.3-12 	树插入的一个递归版本
void MyTreeInsert(BSTree **t,BSTree *p,int k)
{
	if(*t==NULL)
	{
		(*t)=(BSTree *)malloc(sizeof(BSTree));
		(*t)->key=k;
		(*t)->left=NULL;
		(*t)->right=NULL;
		(*t)->p=p;
		if(p!=NULL)
		{
			if(p->key<k)
				p->right=*t;
			else
				p->left=*t;
		}
		return;
	}
	else if((*t)->key>k)
	{
		MyTreeInsert(&((*t)->left),*t,k);
	}
	else
	{
		MyTreeInsert(&((*t)->right),*t,k);
	}
}


//12.3-3 n*n    nlogn
//
//
//















