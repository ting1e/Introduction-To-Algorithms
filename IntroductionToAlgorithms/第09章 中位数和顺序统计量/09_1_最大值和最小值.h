#pragma once
#include "..\base.h"

int Minimum(int a[], int size)
{
	int min = a[0];
	for (int i = 1; i < size; i++)
	{
		min = min > a[i] ? a[i] : min;
	}
	return min;
}

void MaxAndMin(int a[], int size, int *_max, int *_min)
{
	int temp_max, temp_min, max, min;

	if ((size & 1) == 1)
	{
		max = a[size-1];
		min = a[size-1];
	}
	else
	{
		max = a[size-1] > a[size-2] ? a[size-1] : a[size-2];
		min = a[size - 1] > a[size - 2] ? a[size - 2] : a[size - 1];
	}

	for (int i = 0; i < size/2; i++)
	{
		if (a[2 * i] > a[2 * i + 1])
		{
			temp_max = a[2 * i];
			temp_min = a[2 * i + 1];
		}
		else
		{
			temp_min = a[2 * i];
			temp_max = a[2 * i + 1];
		}
		if (temp_max > max)
			max = temp_max;
		if (temp_min < min)
			min = temp_min;
	}

	*_min = min;
	*_max = max;
}

void FindTest()
{
	int a[] = { 5,6,9,1,5,10,111,20,0 };
	int max, min;
	MaxAndMin(a, 9, &max, &min);
}


/*	
	练习9.1-1

	1.找最小元素的比较次数至少为n-1
	2.次小值一定是在step1中与最小元素直接比较的过程中被淘汰的那些数
	最坏情况 lgn -1

	决策树。。。
*/