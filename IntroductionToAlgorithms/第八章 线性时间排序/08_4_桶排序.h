#pragma once
#include "..\base.h"

typedef struct ELEMENT
{
	double x;
	struct ELEMENT *next;
}Element;

void InsertAnElement(Element *e, double a)	//链表尾部插入一个数据
{
	while (e->next)
		e = e->next;
	Element *new_one = (Element *)malloc(sizeof(Element));
	new_one->next = NULL;
	new_one->x = a;
	e->next = new_one;
}

void InsertSort(Element *e) //链表插入排序
{
	if (e->next == NULL)
		return;
	Element *current = e->next->next;
	e->next->next = NULL;
	while (current)
	{
		Element *target = e;
		while (target->next!=NULL&&target->next->x<current->x)
		{
			target = target->next;
		}
		Element *temp = current;
		current = current->next;
		temp->next = target->next;
		target->next = temp;
	}
}


/*
桶排序：
	将【0，1】区间划分为n个相同大小的子区间或称为桶，然后将这n个数放到各个桶中
*/
void BucketSort(double a[], int size)  
{
	Element *b = (Element *)malloc(sizeof(Element)*size);
	for (int i = 0; i < size; i++)
	{
		b[i].next = NULL;
	}
	for (int i = 0; i < size; i++)
	{
		InsertAnElement(&b[(int)(a[i] * size)], a[i]);
	}
	for (int i = 0; i < size; i++)
	{
		InsertSort(&b[(int)(a[i] * size)]);
	}
	int j = 0;
	for (int i = 0; i < size; i++)
	{
		Element *temp = b[i].next;
		while (temp!=NULL)
		{
			a[j++] = temp->x;
			temp = temp->next;
		}
	}
}

void BucketSortTest()
{
	double a[] = { 0.78,0.17,0.39,0.26,0.72,0.94,0.21,0.12,0.23,0.68 };
	BucketSort(a,10);

}

/*
	练习 8.4-2 当所有数都在一个区间时，因插入排序运行时间为Θ(n²) 故。。。
		修改链表排序的方式，此排序方法最坏情况下的时间代价为O(n lgn)
		
	练习 8.4-3 
	X=0	0.25	
	X=1 0.5
	X=2 0.25
	E(X)=1
	E²(X)=1
	E(X²)=1.5

	练习 8.4-3  r∈(0,1) r分成n段,分别为
	0 - √(1/n),√(1/n) - √(2/n),√(2/n) - √(3/n),.........√((n-1)/n) - 1
*/