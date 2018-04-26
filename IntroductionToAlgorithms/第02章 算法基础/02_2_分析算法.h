#pragma once
#include "..\base.h"

/*
	选择排序思想：
	首先找出数组中最小元素与第一个元素进行交换，
	接着找出次小元素与第二个元素交换，
	依次进行，直到完成排序

	循环次数是数组元素个数-1，依次寻找各个元素后，
	最后剩下的就是就是最大的元素。保存在最后的位置。
*/

//练习2.2 - 2 选择算法
void SelectionSort(int array[], int length)
{
	for (int i = 0; i < length-1; i++)
	{
		int min = array[i];
		int min_index = i;
		for (int j = i + 1; j < length; j++)
		{
			if (min > array[j])
			{
				min = array[j];
				min_index = j;
			}
		}
		int temp = array[i];
		array[i] = min;
		array[min_index] = temp;
	}
}

//直接选择排序简单测试
void SelectionSortTest()
{
	int a[5] = { 1,4,5,2,3 };
	SelectionSort(a, 5);
}

/*
练习2.3 - 3
	设数组长度为n
	average:		(1+2+3+4+...+n)/2=(n+1)/2
	worset(max) :	n
*/