#pragma once
#include "..\base.h"
#include "06_1_堆_2_堆的性质.h"
#include "06_3_建堆.h"

/*
	堆排序算法： 数组中的最大元素总在根节点1中，通过把它与堆中最后一个节点互换，
	然后把最后一个节点堆中去除。然后调用MaxHeapify构造一个新的最大堆，知道堆的大小
	降到2
*/

void HeapSort(int a[], int length)
{
	BuildMaxHeap(a, length);
	for (int i = length; i > 1; i--)
	{
		int temp = a[1];
		a[1] = a[i];
		a[i] = temp;
		MaxHeapify(a, 1, i-1);
	}
}

void HeapSortTest()
{
	int a[] = { 0,16,14,10,8,7,9,3,2,4,1 };
	HeapSort(a, 10);
}
