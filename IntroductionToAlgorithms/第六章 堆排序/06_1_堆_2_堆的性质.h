#pragma once
#include "..\base.h"

#define PARENT(i) (i/2)
#define LEFT(i)	(2*i)
#define RIGHT(i) (2*i+1)

//	数组下标为0的元素使用

 /*
	练习6.1-1	高度为h
	max	1*2*4*8.....*2^(n)=2^(n+1)-1
	min	1*2*4*8.....*2(n-1)=2^n

	练习6.1-2 lgn 高度的元素和范围为(n,2n-1)
	故原题得证
*/

//6.2	 

// 从 i，left，right 中选出最大的，下表存储在max中，如果max==i 结束
//	交换max与i所对应的值，此时max对应的原来的i的值，然后递归调用MaxHeapify 
void MaxHeapify(int a[], int i,int heap_size)
{
	int left = LEFT(i);
	int right = RIGHT(i);
	int max = i;
	if (left <= heap_size )
	{
		max = a[max] > a[left] ? max : left;
	}
	if (right <= heap_size)
	{
		max = a[max] > a[right] ? max : right;
	}
	if (max != i)
	{
		int temp = a[max];
		a[max] = a[i];
		a[i] = temp;
		MaxHeapify(a, max, heap_size);
	}
}


// 联系6.2-2 最小堆
void MinHeapify(int a[], int i, int heap_size)
{
	int left = LEFT(i);
	int right = RIGHT(i);
	int min = i;
	if (left <= heap_size)
	{
		min = a[min] < a[left] ? min : left;
	}
	if (right <= heap_size)
	{
		min = a[min] < a[right] ? min : right;
	}
	if (min != i)
	{
		int temp = a[min];
		a[min] = a[i];
		a[i] = temp;
		MinHeapify(a, min, heap_size);
	}
}

//6.2-5	非递归最大堆
void MaxHeapify_(int a[], int i, int heap_size)
{
	int max,right,left;
	max = i;
	do
	{
		i = max;
		left = LEFT(i);
		right = RIGHT(i);
		if (left <= heap_size)
		{
			max = a[max] > a[left] ? max : left;
		}
		if (right <= heap_size)
		{
			max = a[max] > a[right] ? max : right;
		}

		int temp = a[max];
		a[max] = a[i];
		a[i] = temp;
	} while (max != i);
}

void Test()
{
	int a[11] = { 0,16,4,10,14,7,9,3,2,8,1 };
	MaxHeapify(a, 2, 10);
}

