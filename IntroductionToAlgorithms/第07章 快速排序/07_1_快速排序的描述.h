#pragma once
#include "..\base.h"

/*
	快排描述：
	将数组a[p...q]分成两个子数组使得a[p...r-1]中的元素小于或等于a[r],
	a[r+1....q]中的元素大于或等于a[r]，然后通过递归调用快排，对a[p...r-1]
	和a[r+1...q]进行排序
*/

int Partition(int a[], int start, int end)	 //point ..
{
	int x = a[start];
	int j = start;		//j下标指向的节点及之前所有节点必定小于x
						//遍历结束后j下标后面的所有节点必定大于或等于x
	for (int i = start + 1; i <= end; i ++ )	//i 遍历数组找出所有小于x的
	{											//使之完成j下标的意义
		if (a[i] < x)
		{
			j++;
			int temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
	}
	a[start] = a[j];
	a[j] = x;
	return j;
}
//书上所给出的Partition。	
int _Partition(int a[], int p, int r)
{
	int x = a[r];
	int i = p - 1;
	for (int j = p; j < r; j++)
	{
		if (a[j] <= x)
		{
			i++;
			int temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
	}
	a[r] = a[i + 1];
	a[i + 1] = x;

	/*
		练习7.1-2
		if((i+2)==x)
			return (p+r)/2;
	*/
	return i + 1;
}


void QuickSort(int a[], int start, int end)
{
	if (start < end)
	{
		int i = Partition(a, start, end);
		QuickSort(a, start, i - 1);
		QuickSort(a, i + 1, end);
	}
}

void QuickSortTest()
{
	int a[] = { 5,6,1,3,7,8,9,10,2,4 };
	QuickSort(a, 0, 9);
}