#pragma once

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
		while ((j >= 0)&&(array[j]>key))
		{
			array[j + 1] = array[j--];
		}
		array[j + 1] = key;
	}
}




