#pragma once
#include "..//base.h"


#define dn 50
typedef struct FIB_NODE
{
	int key;
	int degree;
	int mark;
	struct FIB_NODE *left;
	struct FIB_NODE *right;
	struct FIB_NODE *parent;
	struct FIB_NODE *child;
}FibNode;

typedef struct FIB_HEAP
{
	int n;
	FibNode *min_node;
}FibHeap;

FibNode *CreateNode(int x,int ma)
{
	FibNode *fib_node = (FibNode *)malloc(sizeof(FibNode));
	fib_node->degree = 0;
	fib_node->key = x;
	fib_node->mark = ma;
	fib_node->parent = NULL;
	fib_node->child = NULL;
	fib_node->left = fib_node;
	fib_node->right = fib_node;
	return fib_node;
}

void FibHeapInsert(FibHeap *fibheap, FibNode *fib_node)
{

	if (fibheap->min_node == NULL)
	{
		fib_node->left = fib_node;
		fib_node->right = fib_node;
		fibheap->min_node = fib_node;
	}
	else
	{
		fib_node->right = fibheap->min_node;
		fib_node->left = fibheap->min_node->left;
		fibheap->min_node->left->right = fib_node;
		fibheap->min_node->left = fib_node;
		if (fib_node->key < fibheap->min_node->key)
			fibheap->min_node = fib_node;
	}
	fib_node->parent = NULL;
	fibheap->n++;
}

FibHeap *MakeFibHeap()
{
	FibHeap *fib_heap = (FibHeap*)malloc(sizeof(FibHeap));
	fib_heap->min_node = NULL;
	fib_heap->n = 0;
	return fib_heap;
}

FibHeap *FibHeapUnion(FibHeap *heap1, FibHeap *heap2)
{
	FibHeap *heap = MakeFibHeap();
	heap->min_node = heap1->min_node;
	if ((heap1->min_node == NULL) || ((heap2->min_node != NULL) && (heap2->min_node->key < heap1->min_node->key)))
	{
		heap->min_node = heap2->min_node;
	}
	if (heap1->min_node != NULL && heap2->min_node != NULL)
	{
		heap1->min_node->left->right = heap2->min_node->left;
		heap2->min_node->left->right = heap1->min_node->left;
		heap1->min_node->left = heap2->min_node;
		heap2->min_node->left = heap1->min_node;
	}
	heap->n = heap1->n + heap2->n;
	return heap;
}

void FibHeapLink(FibHeap *heap, FibNode *y, FibNode *x)
{
	y->left->right = y->right;
	y->right->left = y->left;
	if (x->child == NULL)
	{
		x->child = y;
		y->parent = x;
		y->left = y;
		y->right = y;
	}
	else
	{
		x->child->left->right = y;
		y->left = x->child->left;
		x->child->left = y;
		y->right = x->child;
		y->parent = x;
	}
	x->degree++;
	y->mark = 0;
}
void Consolidate(FibHeap *heap)
{
	FibNode *a[dn] = { 0 };
	FibNode *x = heap->min_node;
	do
	{
		int d = x->degree;
		while (a[d]!=NULL&&d<dn)
		{
			if (a[d] == heap->min_node)
			{
				heap->min_node = heap->min_node->right;
			}
			FibNode *y = a[d];
			if (x->key > y->key)
			{
				FibNode *temp = x;
				x = y;
				y = temp;
			}
			FibHeapLink(heap, y, x);
			a[d] = NULL;
			d++;
		}
		a[d] = x;
		x = x->right;
	} while (x != heap->min_node);
	heap->min_node = NULL;

	for (int i = 0; i < dn; i++)
	{
		if (a[i] != NULL)
		{
			if (heap->min_node == NULL)
			{
				a[i]->left = a[i];
				a[i]->right = a[i];
				heap->min_node = a[i];
			}
			else
			{
				a[i]->left = heap->min_node->left;
				a[i]->right = heap->min_node;
				heap->min_node->left->right = a[i];
				heap->min_node->left = a[i];
				if (a[i]->key < heap->min_node->key)
				{
					heap->min_node = a[i];
				}
			}
		}
	}

}

FibNode *FibHeapExtractMin(FibHeap *heap)
{
	FibNode *min = heap->min_node;
	if (min != NULL)
	{
		min->left->right = min->child;
		min->right->left = min->child->left;
		min->child->left->right = min->right;
		min->child->left = min->left;
		if (min == min->right)
		{
			heap->min_node = NULL;
		}
		else
		{
			heap->min_node = min->right;
			Consolidate(heap);
		}
		heap->n--;
	}
	return min;
}

void Cut(FibHeap *heap, FibNode *x, FibNode *y)
{
	if (y->degree == 1)
	{
		y->child = 0;
	}
	else
	{
		if (x == y->child)
		{
			y->child = x->right;
		}
		x->left->right = x->right;
		x->right->left = x->left;
	}
	y->degree--;
	x->mark = 0;
	FibHeapInsert(heap, x);
}

void CascadingCut(FibHeap *heap, FibNode *y)
{
	FibNode *z = y->parent;
	if (z != NULL)
	{
		if (y->mark == 0)
		{
			y->mark = 1;
		}
		else
		{
			Cut(heap, y, z);
			CascadingCut(heap, z);
		}
	}
}

void FibHeapDecreaseKey(FibHeap *heap, FibNode *x, int k)
{
	if (k > x->key)
		return;
	x->key = k;
	FibNode *y = x->parent;
	if (y != NULL && x->key < y->key)
	{
		Cut(heap, x, y);
		CascadingCut(heap, y);
	}
	if (x->key < heap->min_node->key)
	{
		heap->min_node = x;
	}
}

void FibHeapDelete(FibHeap *heap, FibNode *node)
{
	FibHeapDecreaseKey(heap, node, INT_MIN);
	FibHeapExtractMin(heap);
}


void test()
{
	FibHeap *heap = MakeFibHeap();
	FibNode *node3 = CreateNode(3, 0);
	FibNode *node18 = CreateNode(18, 1);
	FibNode *node39 = CreateNode(39, 1);
	node18->child = node39;
	node39->parent = node18;
	FibNode *node52 = CreateNode(52, 0);
	FibNode *node38 = CreateNode(38, 0);
	FibNode *node41 = CreateNode(41, 0);
	node38->child = node41;
	
	node18->right = node52;
	node52->right = node38;
	node38->right = node18;
	node18->left = node38;
	node52->left = node18;
	node38->left = node52;
	node3->child = node52;
	node41->parent = node38;
	node39->parent = node18;

	node52->parent = node3;
	node38->parent = node3;
	node18->parent = node3;

	node3->degree = 3;
	node18->degree = 1;
	node38->degree = 1;

	FibNode *node17 = CreateNode(17, 0);
	FibNode *node30 = CreateNode(30, 0);
	node17->child = node30;
	node30->parent = node17;
	node17->degree = 1;

	FibNode *node46 = CreateNode(46, 0);
	FibNode *node24 = CreateNode(24, 0);
	FibNode *node26 = CreateNode(26, 1);
	FibNode *node35 = CreateNode(35, 0);
	node26->child = node35;
	node35->parent = node26;
	node26->left = node46;
	node46->left = node26;
	node26->right = node46;
	node46->right = node26;
	node24->child = node26;
	node26->parent = node24;
	node46->parent = node24;
	node24->degree = 2;
	node26->degree=1;

	
	FibHeapInsert(heap, node17);
	FibHeapInsert(heap, node24);
	FibHeapInsert(heap, node3);
	FibHeapInsert(heap, CreateNode(23, 0));
	FibHeapInsert(heap, CreateNode(7, 0));
	FibHeapInsert(heap, CreateNode(21, 0));
	heap->n = 15;
	FibHeapExtractMin(heap);
	FibHeapDecreaseKey(heap, node46, 5);
	printf("1234");
}