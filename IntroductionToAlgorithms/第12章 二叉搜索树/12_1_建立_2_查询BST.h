#pragma once
#include "..\base.h"

typedef struct BINARYSEARCHTREE
{
	int key;
	struct BINARYSEARCHTREE *left;
	struct BINARYSEARCHTREE *right;
	struct BINARYSEARCHTREE *p;
}BSTree;



//you need to make sure the array observe the rule of bst
//
//
BSTree *BuildTree(BSTree *parent, int a[],int i,int size)
{
	BSTree *head=NULL;
	if(i<size)
	{
		head =(BSTree *)malloc(sizeof(BSTree));
		head->p=parent;
		head->key=a[i];
		
		head->left=BuildTree(head,a,2*i+1,size);
		head->right=BuildTree(head,a,2*i+2,size);
	}

	return head;
}
//
void InorderTreeWalk(BSTree *root)
{
	if(root!=NULL)
	{
		InorderTreeWalk(root->left);
		printf("%d   ",root->key);
		InorderTreeWalk(root->right);
	}
}

//练习12.1-3
//非递归遍历算法

void InorderNoRecursion(BSTree *root)
{
	if(root==NULL)
		return ;
	BSTree *current=root;
	BSTree *child=NULL;
	while(1)
	{
		if(child!=current->left)
		{
			while(current->left)
				current=current->left;
		}
		printf("%d   ",current->key);
		if(current->right)
		{
			current=current->right;
			continue;
		}
		do
		{
			child=current;
			current=current->p;
			if(current==NULL)
				return;

		}while(child==current->right);
	}

}


BSTree *TreeSearch(BSTree *root,int k)
{
	//递归版本
	if(root==NULL||root->key==k)
	{
		return root;
	}
	if(k<root->key)
	{
		return TreeSearch(root->left,k);
	}
	else
	{
		return TreeSearch(root->right,k);
	}
}

//迭代版本
BSTree *IterativeTreeSearch(BSTree *root,int k)
{
	while(root!=NULL&&k!=root->key)
	{
		if(k<root->key)
		{
			root=root->left;
		}
		else
		{
			root=root->right;
		}
	}
	return root;
}

BSTree *TreeMinimum(BSTree *root)
{
	while(root->left)
		root=root->left;
	return root;
}

BSTree *TreeMaximum(BSTree *root)
{
	while(root->right)
		root=root->right;
	return root;
}

BSTree *TreeSuccessor(BSTree *x)
{
	if(x->right!=NULL)
	{
		return TreeMinimum(x->right);
	}
	
	BSTree *y=x->p;
	while(y!=NULL&&x==y->right)
	{
		x=y;
		y=y->p;
	}
	return y;

}

BSTree *TreePredecessor(BSTree *x)
{
	if(x->left)
	{
		TreeMaximum(x->left);

	}
	BSTree *y=x->p;
	while(y!=NULL&&x==y->left)
	{
		x=y;
		y=y->p;
	}
	return y;
}

// 12.2-1 c不是查找过的序列
//
//
//
//12.2-2 非递归版本 原理一致所以只写一个啦
//
BSTree *TreeMinimum1(BSTree *root)
{
	if(root->left)
	{
		TreeMinimum1(root->left);
	}
	else
	{
		return root;
	}
}

//
//12.2-5 二叉树中一个节点的后继，一定在此节点的右侧，而且是此侧最小的节点，如果这个节点还有左孩子，那么它一定不是最小的节点
//   	前驱同理
//
//
//12.2-6 如果一个节点没有右子树，那它的后继一定不是它的子节点而是它的某个祖先，因为父节点一定大于左子树上所有节点，而小于右子树上所有节点
//  	如果这个后继的左孩子不是它的祖先，那个这个后继的右孩子是它的祖先，因父节点一定大于右子树上所有节点，不可能是他的后继，故不成立
//  	因而原题得证。
// 
//
//
//
//
//
//
//
//
//















