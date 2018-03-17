#pragma once
#include "..\base.h"
/* 
插入排序思想：
		数组中下标 i 表示当前排序的元素，
		那么0到i-1为已经排序好的元素，
		在其中找到i的位置并排序。
*/

void InsertSort(int *array, int length)
{
	int key,j;
	for (int i = 1; i < length; i++)
	{
		key = array[i];
		j = i - 1;
		while ((j >= 0)&&(array[j]>key)) //练习2.1-2  改成 array[j]<key
		{
			array[j + 1] = array[j--];
		}
		array[j + 1] = key;
	}
}

//插入排序简单测试
void InsertSortTest()
{
	int a[5] = { 1,4,5,2,3 };
	InsertSort(a, 5);
}

//练习2.1 - 3
void FindV(int array[], int length,int v)
{
	int i;
	for (i = 0; i < length; i++)
	{
		if (array[i] == v)
		{
			return;
		}
	}
	if (i == length)
		v = -1;	// v未出现赋值为特殊值
}

//练习2.1 - 4
void TwoBinNumAdd(int first[], int second[],int sum[] ,int length)
{
	for (int i = 0; i < length; i++)
	{
		sum[i + 1] = first[i] + second[i];
	}
	for (int i = length; i > 0; i--)
	{
		if (sum[i] >= 2)
		{
			sum[i] -= 2;
			sum[i - 1] += 1;
		}
	}
}
// 练习2.1 - 4 测试
void TwoBinNumAddTest()
{
	int first[4] = { 1,1,0,1 };
	int second[4] = { 1,1,0,0 };
	int sum[5] = { 0 };
	TwoBinNumAdd(first, second, sum, 5);
}
/*
	练习2.1-1	A{31,41,59,26,41,58}	
				A{31,41,59,26,41,58}	i=1
				A{31,41,59,26,41,58}		2
				A{26,31,41,59,41,58}		3
				A{26,31,41,41,59,58}		4
				A{26,31,41,41,58,59}		5
*/

