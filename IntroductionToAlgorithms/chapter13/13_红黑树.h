#include "..//base.h"


//假设所有NULL都为黑色叶子节点

enum Color{red,black};

typedef struct RBTREE
{
	enum Color color;
	int key;
	struct RBTREE *left;
	struct RBTREE *right;
	struct RBTREE *p;
} RBTree;

//中序遍历

void InOrder(RBTree *root)
{
	static char *_color[]={"red","black"};
	if(root!=NULL)
	{
		InOrder(root->left);
		printf("%d %s ",root->key,_color[root->color]);
		InOrder(root->right);
	}
}


//
//
//旋转
//向左旋转

void LeftRotate(RBTree **root,RBTree *x)
{
	RBTree *y=x->right;
	x->right=y->left;
	if(y->left!=NULL)
	{
		y->left->p=x;
	}
	y->p=x->p;
	if(x==*root)
	{
		*root=y;
	}
	else if(x==x->p->left)
	{
		x->p->left=y;
	}
	else
	{
		x->p->right=y;
	}
	y->left=x;
	x->p=y;
}

//练习 13.2-1 向右旋转

void RightRotate(RBTree **root,RBTree *y)
{
	RBTree *x=y->left;
	y->left=x->right;
	if(x->right!=NULL)
	{
		x->right->p=y;
	}
	x->p=y->p;
	if(y==*root)
	{
		*root=x;
	}
	else if(y==y->p->left)
	{
		x->p->left=x;
	}
	else
	{
		x->p->right=x;
	}
	x->right=y;
	y->p=x;
}

void RBInsertFixup(RBTree **root,RBTree *z)
{
	RBTree *y=NULL;
	while(z->p!=NULL&&z->p->color==red)
	{
		if(z->p==z->p->p->left)
		{
			y=z->p->p->right;
			if(y!=NULL&&y->color==red)
			{
				z->p->color=black;
				y->color=black;
				z->p->p->color=red;
				z=z->p->p;
			}
			else if(z==z->p->right)
			{
				z=z->p;
				LeftRotate(root,z);
			}
			else
			{
				z->p->color=black;
				z->p->p->color=red;
				RightRotate(root,z->p->p);
			}
		}
		else
		{

			y=z->p->p->left;
			if(y!=NULL&&y->color==red)
			{
				z->p->color=black;
				y->color=black;
				z->p->p->color=red;
				z=z->p->p;
			}
			else if(z==z->p->left)
			{
				z=z->p;
				LeftRotate(root,z);
			}
			else
			{
				z->p->color=black;
				z->p->p->color=red;
				LeftRotate(root,z->p->p);
			}
		}
	}
	(*root)->color=black;
}




void RBInsert(RBTree **root,int k)
{
	RBTree *y=NULL;
	RBTree *x=*root;
	while(x!=NULL)
	{
		y=x;
		if(k<x->key)
		{
			x=x->left;
		}
		else
		{
			x=x->right;
		}
	}
	RBTree *node=(RBTree *)malloc(sizeof(RBTree));
	node->key=k;
	node->left=NULL;
	node->right=NULL;
	node->color=red;
	node->p=y;
	if(y==NULL)
	{
		node->color=black;
		*root=node;
		return;
	}
	else if(k<y->key)
	{
		y->left=node;
	}
	else
	{
		y->right=node;
	}
	RBInsertFixup(root,node);
}




// 练习 13.3-1 那样会破坏性质5.。
//
// 练习 13.3-2 		r==red  b==black
//    			
//     	               38 b
//     		31 r	     41 b
//          12 b    19 b 	
//        8r
//
//练习 13.3-4 
// 	将节点颜色改成红色的只有三处，而且这三处改变的节点都是不可能是nil节点。
//
//练习 13.3-6 
// 	可以写一个找出父指针的函数代替



void RBTransplant(RBTree **root,RBTree *u,RBTree *v)
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
	v->p=u->p;
}


RBTree *RBMinimum(RBTree *x)
{
	if(x==NULL)
		return NULL;
	while(x->left!=NULL)
		x=x->right;
	return x;
}











