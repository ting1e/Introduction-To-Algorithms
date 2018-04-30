#pragma once
#include "../第07章 快速排序\07_3_快速排序的随机化版本.h"

/*
	找出数组中第i小的数据：
	算法一第七章的快速排序为模型，将输入数组进行递归划分，然后处理划分的一边。
*/

int RandomizedSelect(int a[], int start, int end, int i)
{
	if (start == end)
		return a[start];
	int middle = RandomizedPartition(a, start, end);
	int k = middle - start + 1;  //shit....
	if (k == i)
		return a[middle];
	else if (i < k)
	{
		return RandomizedSelect(a, start, middle - 1, i);
	}
	else
	{
		return RandomizedSelect(a, middle + 1, end, i - k);
	}

}


//练习9.2-3
int CircleSelect(int a[], int start, int end, int i)
{
	int middle,k;
	while (start<end)
	{
		middle = RandomizedPartition(a, start, end);
		k = middle - start + 1;
		if (k == i)
			return a[middle];
		else if (i < k)
		{
			end = middle - 1;
		}
		else
		{
			start = middle + 1;
			i = i - k;
		}
	}
	return a[start];
}

void RandomizedSelectTest()
{
	int a[] = { 5,6,1,3,7,8,9,10,2,4 };
	int i = CircleSelect(a, 0, 9, 1);
}

/*
	练习9.2-1 如果长度为零的在左侧，那个k必定等于1，i必定大于k，所以不可能选择长度为0的
	那一部分，右侧类似。

	练习9.2-4 每次都将最大的那个值作中间值。
*/