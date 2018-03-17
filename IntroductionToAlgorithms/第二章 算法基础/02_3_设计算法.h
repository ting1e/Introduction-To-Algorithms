#pragma once
#include "..\base.h"

/*
	归并排序：对数组进行排序时，先将数组分成两个部分，
	对每个部分排序时，先将这个部分分成两个部分，直到不能分割
	然后再将每个排序好的部分综合起来进行排序
*/

// 书上伪代码所给出的归并排序
void Merge(int array[], int start, int middle, int end)
{
	int i,j,k;
	int n1 = middle - start + 1;
	int n2 = end - middle;
	int *left = (int *)malloc((sizeof(int))*n1);
	int *right = (int *)malloc((sizeof(int))*n2);

	for (i = 0; i < n1; i++)
	{
		left[i] = array[start + i];
	}
	for (i = 0; i < n2; i++)
	{
		right[i] = array[middle + i + 1];
	}
	i = 0;
	j = 0;
	for (k = start; k <= end; k++)
	{
		if ((i == n1) || (j == n2))
		{
			if (i == n1)
			{
				array[k] = right[j++];
			}
			else
			{
				array[k] = left[i++];
			}
		}
		else
		{
			if (left[i]<=right[j])
			{
				array[k] = left[i++];
			}
			else
			{
				array[k] = right[j++];
			}
		}
	}
	free(left);
	free(right);
}

//归并递归调用
void MergeSort(int array[],int start,int end)
{
	if (start < end)
	{
		int middle = (start + end) / 2;
		MergeSort(array, start, middle);
		MergeSort(array, middle + 1, end);
		Merge(array, start, middle, end);
	}
}
//归并排序简单测试
void MergeSortTest()
{
	int arr[8] = { 2,4,5,7,1,2,3,6 };
	MergeSort(arr, 0, 7);

}
//将归并排序的两个函数合成一个,其实是一样的
void MyMergeSort(int array[], int start, int end)
{
	if (start < end)
	{
		int middle = (start + end) / 2;
		MyMergeSort(array, start, middle);
		MyMergeSort(array, middle + 1, end);
		int i, j, k;
		int n1 = middle - start + 1;
		int n2 = end - middle;
		//因vs2017不支持变长数组，所以采用malloc函数。
		int *left = (int *)malloc((sizeof(int))*n1);
		int *right = (int *)malloc((sizeof(int))*n2);

		for (i = 0; i < n1; i++)
		{
			left[i] = array[start + i];
		}
		for (i = 0; i < n2; i++)
		{
			right[i] = array[middle + i + 1];
		}
		i = 0;
		j = 0;
		for (k = start; k <= end; k++)
		{
			if ((i == n1) || (j == n2))
			{
				if (i == n1)
				{
					array[k] = right[j++];
				}
				else
				{
					array[k] = left[i++];
				}
			}
			else
			{
				if (left[i] <= right[j])
				{
					array[k] = left[i++];
				}
				else
				{
					array[k] = right[j++];
				}
			}
		}
		free(left);
		free(right);
	}
}
//练习2.3-4	插入排序的递归版本
void RecursionInsertSort(int array[], int length)
{
	if (length > 1)
	{
		RecursionInsertSort(array, length - 1);
		int i = length - 2;
		int key = array[length - 1];
		while (i >= 0 && key < array[i])
		{
			array[i + 1] = array[i--];
		}
		array[i + 1] = key;
	}
}

//插入排序的递归版本简单测试
void RecursionInsertSortMergeSortTest()
{
	int arr[8] = { 2,4,5,7,1,2,3,6 };
	RecursionInsertSort(arr, 8);

}

//2.3-5 二分查找算法
int BinarySearch(int array[], int start,int end, int v)
{
	while (start<=end)
	{
		int mid = (end + start) / 2 ;
		if (array[mid] > v)
		{
			end = mid - 1;
		}
		else if (array[mid] == v)
		{
			return mid;
		}
		else
		{
			start = mid + 1;
		}
	}
	return start;
}

//2.3-5 二分查找算法测试
void BinarySearchTest()
{
	
	int arr[8] = { 2,4,5,7,1,2,3,6 };
	RecursionInsertSort(arr, 8);
	int i = BinarySearch(arr, 0, 7, 6);

}



//2.3-6 带二分查找的插入排序	二分查找算法为练习2.3-5
void InsertSort(int *array, int length)
{
	int key, j,k=0;
	for (int i = 1; i < length; i++)
	{
		key = array[i];
		k=BinarySearch(array, 0, i - 1, key);
		j = i - 1;
		while (j >= k) 
		{
			array[j + 1] = array[j--];
		}
		array[j + 1] = key;
	}
}

//二分插入排序测试
void InsertSortTest()
{
	int a[5] = { 1,4,5,2,3 };
	InsertSort(a, 5);
}

/*
	练习2.3-1	A{3,41,52,26,38,57,9,49}

                      3 9 26 38 41 49 52 57

	       3  26  41  52                9  38  49  57

	  3	  41         26   52          38   57         9   49

	3		41		52		26		38		57		9		49

*/