#pragma once
#include "..\base.h"
#include "07_1_¿ìËÙÅÅÐòµÄÃèÊö.h"

//Á·Ï° 7.4-6
int __Partition(int a[], int p, int q)
{
	int x = Random(p, q);
	int y = Random(p, q);
	int z = Random(p, q);
	int max = a[x] > a[y] ? x : y;
	max = a[max] > a[z] ? max : z;
	int min = a[x] > a[y] ? y : x;
	min = a[min] > a[z] ? z : min;
	int mid = x + y + z - min - max;
	int temp = a[mid];
	a[mid] = a[q];
	a[q] = temp;
	return _Partition(a, p, q);
	
}

//Ë¼¿¼Ìâ7-1
int HoarePartition(int a[], int p, int r)
{
	int x = a[p];
	int i = p;
	int j = r;
	while (1)
	{
		if (a[i] >= x)
		{
			if (a[j] <= x)
			{
				if (i < j)
				{
					int temp = a[i];
					a[i] = a[j];
					a[j] = temp;
				}
				else
				{
					return j;
				}
			}
			else
			{
				j--;
			}
		}
		else
		{
			i++;
		}


	}
}

void _QuickSort(int a[], int start, int end)
{
	if (start < end)
	{
		int i = HoarePartition(a, start, end);
		_QuickSort(a, start, i - 1);
		_QuickSort(a, i + 1, end);
	}
}

//Ë¼¿¼7-4	Î²µÝ¹é
void TailRecursiveQuickSort(int a[], int start, int end)
{
	while (start<end)
	{
		int q = Partition(a, start, end);
		TailRecursiveQuickSort(a, start, q - 1);
		start = q + 1;
	}
}

//Î²µÝ¹éÓÅ»¯
void  OptimizeTailQuickSort(int a[], int start, int end)
{
	while (start<end)
	{
		int q = Partition(a, start, end);
		if (q - start < end - q)
		{
			OptimizeTailQuickSort(a, start, q-1);
			start = q + 1;
		}
		else
		{
			OptimizeTailQuickSort(a, q + 1, end);
			end = q - 1;
		}
	}
}


void _QuickSortTest()
{
	int a[] = { 5,6,1,3,7,8,9,10,2,4 };
	OptimizeTailQuickSort(a, 0, 9);
}