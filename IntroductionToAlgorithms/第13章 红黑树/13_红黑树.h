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

//红黑书搜索节点
RBTree *TreeSearch(RBTree *root, int k)
{
	while (root != NULL && k != root->key)
	{
		if (k<root->key)
		{
			root = root->left;
		}
		else
		{
			root = root->right;
		}
	}
	return root;
}



//中序遍历

void InOrder(RBTree *root)
{
	static char _color[2][6]={"red","black"};
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
	if (v != NULL)
		v->p = u->p;
}


RBTree *RBMinimum(RBTree *x)
{
	if(x==NULL)
		return NULL;
	while(x->left!=NULL)
		x=x->right;
	return x;
}


void RBDeleteFixup(RBTree **root,RBTree *x)
{
	RBTree *w=NULL;
	while(x!=NULL&&x->color==black)
	{
		if(x==x->p->left)
		{
			w=x->p->right;
			if(w->color==red)
			{
				w->color=black;
				x->p->color=red;
				LeftRotate(root,x->p);
				w=x->p->right;
			}
			if(w->left->color==black&&w->right->color==black)
			{
				w->color=red;
				x=x->p;
			}
			else if(w->right->color==black)
			{
				w->left->color=black;
				w->color=red;
				RightRotate(root,w);
				w=x->p->right;
			}
			w->color=x->p->color;
			x->p->color=black;
			w->right->color=black;
			LeftRotate(root,x->p);
			x=*root;
		}
		else
		{

			w=x->p->left;
			if(w->color==red)
			{
				w->color=black;
				x->p->color=red;
				LeftRotate(root,x->p);
				w=x->p->left;
			}
			if(w->right->color==black&&w->left->color==black)
			{
				w->color=red;
				x=x->p;
			}
			else if(w->left->color==black)
			{
				w->right->color=black;
				w->color=red;
				RightRotate(root,w);
				w=x->p->left;
			}
			w->color=x->p->color;
			x->p->color=black;
			w->left->color=black;
			LeftRotate(root,x->p);
			x=*root;
		}
	}
	if (x != NULL)
		x->color = black;
}


void RBDelete(RBTree **root,int k)
{
	RBTree *z = TreeSearch(*root, k);
	if (z == NULL)
		return;
	RBTree *y=z;
	RBTree *x=NULL;
	enum Color y_color=y->color;
	if(z->left==NULL)
	{
		x=z->right;
		RBTransplant(root,z,z->right);
	}
	else if(z->right==NULL)
	{
		x=z->left;
		RBTransplant(root,z,z->left);
	}
	else
	{
		y=RBMinimum(z->right);
		y_color=y->color;
		x=y->right;
		if (y->p==z)
			x->p=y;
		else
		{
			RBTransplant(root,y,y->right);
			y->right=z->right;
			y->right->p=y;
		}
		RBTransplant(root,z,y);
		y->left=z->left;
		y->left->p=y;
		y->color=z->color;
	}
	if(y_color==black)
	{
		RBDeleteFixup(root,x);
	}
}




void test()
{
	RBTree *tree = NULL;
	RBInsert(&tree, 19);

	RBInsert(&tree, 3);
	InOrder(tree);
	printf("\n");

	RBInsert(&tree, 5);
	InOrder(tree);
	printf("\n");


	RBInsert(&tree, 6);
	InOrder(tree);
	printf("\n");

	int i;
	for (i = 1; i<20; i++)
	{
		RBInsert(&tree, i);
		if (i % 5 == 0)
			InOrder(tree);
		printf("\n");
	}

	RBDelete(&tree, 1);

	InOrder(tree);
}
