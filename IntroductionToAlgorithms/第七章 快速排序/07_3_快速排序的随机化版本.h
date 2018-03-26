#pragma once
#include "..\base.h"
#include "07_1_快速排序的描述.h"

//随机化的快排，与上节的_Partition对应

int RandomizedPartition(int a[], int p, int r)
{
	int i = Random(p, r);
	int temp = a[i];
	a[i] = a[r];
	a[r] = temp;
	return _Partition(a, p, r);
}

void RandomizedQuickSort(int a[], int p, int r)
{
	if (p < r)
	{
		int q = RandomizedPartition(a, p, r);
		RandomizedQuickSort(a, p, q - 1);
		RandomizedQuickSort(a, q + 1, r);
	}
}

void RandomizedQuickSortTest()
{
	int a[] = { 5,6,1,3,7,8,9,10,2,4 };
	RandomizedQuickSort(a, 0, 9);
}