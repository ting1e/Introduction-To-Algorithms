#pragma once
#include "..//base.h"

#define T 5
int cur_name = 0;
/*
	练习 18.1-1 t=1时，节点上可能没有关键字。

	18.1-2   t=2   

	18.1-4  1+(t-1)(Σ(i=1--h) (t^i))
	
*/

/*
	具体B树文件读写稍微有些麻烦，所以就先不写了,只先实现一个简单的读写操作。
	我的思路是 每个节点存放在一个文件里，这样对B树中的各个节点更改时也更方便
	节点的孩子指向子节点文件名字。
*/
typedef struct BTREE
{
	int n;
	int key[2 * T - 1];
	int is_leaf;
	struct BTREE *children[2 * T];
}BTree;


void DiskWrite(BTree *bt,char fname[]) //存放在btree文件夹下。
{
	char file_name[2 * SIZE];
	sprintf_s(file_name, 2 * SIZE, "btree\\%s.txt", fname);
	FILE *fp;
	fopen_s(&fp, file_name, "w");
	fwrite(bt, sizeof(BTree), 1, fp);
	fclose(fp);
}


BTree *DiskRead(char fname[])
{
	BTree *bt = (BTree *)malloc(sizeof(BTree));
	char file_name[2 * SIZE];
	sprintf_s(file_name, 2 * SIZE, "btree\\%s.txt", fname);
	FILE *fp;
	fopen_s(&fp, file_name, "r");
	fread(bt, sizeof(BTree), 1, fp);
	fclose(fp);
	return bt;
}

void BTreeTraverse(BTree *tree)
{
	if (tree == NULL)
		return;
	if (tree->is_leaf)
	{
		for (int i = 0; i < tree->n; i++)
		{
			printf("%d ", tree->key[i]);
		}
	}
	else
	{
		for (int i = 0; i < tree->n; i++)
		{
			BTreeTraverse(tree->children[i]);
			printf("%d ", tree->key[i]);
		}
		BTreeTraverse(tree->children[tree->n]);
	}
}


BTree *BTreeSearch(BTree *x, int k,int *pos)
{
	int i = 0;
	while (i < x->n&&k > x->key[i])
	{
		i++;
	}
	if (i < x->n&&k == x->key[i])
	{
		*pos = i;
		return x;
	}
	else if (!x->is_leaf)
	{
		return BTreeSearch(x->children[i], k, pos);
	}
	return NULL;
}

BTree *BTreeCreate()
{
	BTree *bt = (BTree *)malloc(sizeof(BTree));
	bt->is_leaf = 1;
	bt->n = 0;
	return bt;
}

void BTreeSplitChild(BTree *x, int i)
{
	BTree *z = (BTree *)malloc(sizeof(BTree));
	BTree *y = x->children[i];
	z->is_leaf = y->is_leaf;
	z->n = T - 1;
	for (int j = 0; j < T - 1; j++)
	{
		z->key[j] = y->key[j + T];
	}
	if (!y->is_leaf)
	{
		for (int j = 0; j < T; j++)
		{
			z->children[j] = y->children[j + T];
		}
	}
	y->n = T - 1;
	for (int j = x->n; j >= i + 1; j--)
	{
		x->children[j + 1] = x->children[j];
	}
	x->children[i+1] = z;
	for (int j = x->n - 1; j >= i; j--)
	{
		x->key[j + 1] = x->key[j];
	}
	x->key[i] = y->key[T-1];
	x->n++;
}


void BTreeInsertNotFull(BTree *x, int k)
{
	int i = x->n;
	if (x->is_leaf)
	{
		while (i>=1&&k<x->key[i-1])
		{
			x->key[i] = x->key[i - 1];
			i--;
		}
		x->key[i] = k;
		x->n++;
	}
	else
	{
		while (i >= 1 && k < x->key[i - 1])
		{
			i--;
		}
		if (x->children[i]->n == 2 * T - 1)
		{
			BTreeSplitChild(x, i);
			if (k > x->key[i])
			{
				i++;
			}
		}

		BTreeInsertNotFull(x->children[i], k);
	}
}
void BTreeInsert(BTree **t, int k)
{
	BTree *r = *t;
	if (r->n == 2 * T - 1)
	{
		BTree *s = (BTree *)malloc(sizeof(BTree));
		*t = s;
		s->is_leaf = 0;
		s->n = 0;
		s->children[0] = r;
		BTreeSplitChild(s, 0);
		BTreeInsertNotFull(s, k);
	}
	else
	{
		BTreeInsertNotFull(r, k);
	}
}

void BTreeLeftRomate(BTree *x,int i)
{
	BTree *y = x->children[i];
	BTree *z = x->children[i + 1];
	y->key[y->n] = x->key[i];
	y->children[y->n + 1] = z->children[0];
	y->n++;
	x->key[i] = z->key[0];
	for (int j = 0; j < z->n - 1; j++)
	{
		z->key[j] = z->key[j + 1];
		z->children[j] = z->children[j + 1];
	}
	z->children[z->n - 1] = z->children[z->n];
	z->n--;
}

void BTreeRightRomate(BTree *x, int i)
{
	BTree *y = x->children[i];
	BTree *z = x->children[i + 1];
	for (int j = z->n; j > 0; j--)
	{
		z->key[j] = z->key[j - 1];
		z->children[j + 1] = z->children[j];
	}
	z->children[1] = z->children[0];
	z->key[0] = x->key[i];
	z->children[0] = y->children[y->n];
	x->key[i] = y->key[y->n - 1];
	y->n--;
}

void BTreeCombine(BTree *x, int i)
{
	BTree *y = x->children[i];
	BTree *z = x->children[i + 1];
	y->key[y->n] = x->key[i];
	y->n++;
	for (int j = i; j < x->n - 1; j++)
	{
		x->key[j] = x->key[j + 1];
		x->children[j + 1] = x->children[j + 2];
	}
	x->n--;
	for (int j = 0; j < z->n; j++)
	{
		y->key[y->n + j] = z->key[j];
		y->children[y->n + j] = z->children[j];
	}
	y->n += z->n;
	y->children[y->n] = z->children[z->n];
	free(z);
}
void BTreeDelete(BTree **t, int k)
{
	BTree *x = *t;
	int i = 0;
	while (i < x->n&&k > x->key[i])
	{
		i++;
	}
	if (k == x->key[i])
	{
		if (x->is_leaf)
		{
			for (int j = i; j < x->n - 1; j++)
			{
				x->key[j] = x->key[j + 1];
			}
			x->n--;
		}
		else
		{
			if (x->children[i]->n >= T)
			{
				x->key[i] = x->children[i]->key[x->children[i]->n - 1];
				BTreeDelete(&(x->children[i]), x->children[i]->key[x->children[i]->n - 1]);
			}
			else if (x->children[i + 1]->n >= T)
			{
				x->key[i + 1] = x->children[i + 1]->key[x->children[i + 1]->n - 1];
				BTreeDelete(&(x->children[i + 1]), x->children[i + 1]->key[x->children[i + 1]->n - 1]);
			}
			else
			{
				BTreeCombine(x, i);
				BTreeDelete(&x->children[i], k);
			}
		}
	}
	else
	{
		if (x->children[i]->n == T - 1)
		{
			if (i > 0 && i < x->n)
			{
				if (x->children[i - 1]->n >= T)
				{
					BTreeRightRomate(x, i - 1);
				}
				else if (x->children[i + 1]->n >= T)
				{
					BTreeLeftRomate(x, i);
				}
				else
				{
					BTreeCombine(x, i);
				}
			}
			else if (i == 0)
			{
				if (x->children[i + 1]->n >= T)
				{
					BTreeLeftRomate(x, 0);
				}
				else
				{
					BTreeCombine(x, 0);
				}
			}
			else if (i == x->n)
			{
				if (x->children[i - 1]->n >= T)
				{
					BTreeRightRomate(x, i - 1);
				}
				else
				{
					BTreeCombine(x, i - 1);
				}
			}
		}
		BTreeDelete(&x->children[i], k);
	}
	if (x->n == 0)
	{
		*t = x->children[0];
		free(x);
	}

}


//fix delete bug
void test()
{
	BTree *bt = BTreeCreate();
	for (int i = 1; i <100; i++)
	{
		BTreeInsert(&bt, i);
	}
	for (int i = 1; i <90; i++)
	{
 		BTreeDelete(&bt, i);
	}

	BTreeTraverse(bt);
	printf("done\n");
}