#pragma once
#include "..\base.h"

//本节几乎所有函数都返回一个指针，使用完成后都应该被手动释放

/*
	问题描述：给出一个数组，数组中的值有正有负，找出数组
	中的子数组，子数组各个值的和应大于任何其他子数组（可能有多个），

	分治策略：
		找到子数组中间的位置mid，最大子数组必定位于这三种情况之一：
		1.在start到mid之间，2.在mid+1到end之间，3.在start到end之间且跨越mid
*/

//找到第三种情况的的结果  该函数返回一个指向有三个int的数组的指针
//(*ret)[0]	最大子数组的左边界
//(*ret)[1]	最大子数组的右边界
//(*ret)[2]	最大子数组各个值得和
int (*FindMaxCrossingSubArray(int array[], int start, int middle, int end))[3]
{
	int(*ret_val)[3] = (int(*)[3])malloc((sizeof(int)) * 3);
	int i;
	int sum = 0, left_sum = array[middle], right_sum = array[middle+1];
	(*ret_val)[0] = middle;
	for (i = middle; i >= start; i--)
	{
		sum += array[i];
		if (sum > left_sum)
		{
			left_sum = sum;
			(*ret_val)[0] = i;
		}
	}

	sum = 0;
	(*ret_val)[1] = middle;
	for (int i = middle+1; i <=end; i++)
	{
		sum += array[i];
		if (sum > right_sum)
		{
			right_sum = sum;
			(*ret_val)[1] = i;
		}
	}
	(*ret_val)[2] = right_sum + left_sum;
	return ret_val;
}

//获得最大子数组的分治算法主体  只返回一个最大子数组
//(*ret)[0]	最大子数组的左边界
//(*ret)[1]	最大子数组的右边界
//(*ret)[2]	最大子数组各个值得和
int(*FindMaxSubArray(int array[], int start,int end))[3]
{
	if (start == end)
	{
		int(*ret_val)[3] = (int(*)[3])malloc((sizeof(int)) * 3);
		(*ret_val)[0] = start;
		(*ret_val)[1] = end;
		(*ret_val)[2] = array[start];
		return ret_val;
	}
	else
	{
		int middle = (start + end) / 2;
		int(*max_left)[3], (*max_right)[3], (*max_cross)[3];
		max_left = FindMaxSubArray(array, start, middle);
		max_right = FindMaxSubArray(array, middle + 1, end); //0.0
		max_cross = FindMaxCrossingSubArray(array, start, middle, end);
		if ((*max_left)[2] >= (*max_right)[2])
		{
			free(max_right);
			if ((*max_left)[2] >= (*max_cross)[2])
			{
				free(max_cross);
				return max_left;
			}
			else
			{
				free(max_left);
				return max_cross;
			}
		}
		else
		{
			free(max_left);
			if ((*max_right)[2] >= (*max_cross)[2])
			{
				free(max_cross);
				return max_right;
			}
			else
			{
				free(max_right);
				return max_cross;
			}
		}

	}
}

/*练习4.1-2 暴力膜  两个思想：
	1. 运用之前的FindMaxCrossingSubArray（）函数。然后middle值从第一个一直到最后一个
	时间复杂度为n*n=n²；
	2.排列问题   时间复杂度为至少大于n²，应该比第一种复杂
*/
int(*FindMaxSubArrayForce1(int array[], int start, int end))[3]
{
	int(*temp)[3];
	int(*max)[3] = (int(*)[3])malloc((sizeof(int)) * 3);
	(*max)[2] = 0;
	for (int i = start; i <= end; i++)
	{
		temp = FindMaxCrossingSubArray(array, start, i, end);
		if ((*temp)[2] > (*max)[2])
		{
			free(max);
			max = temp;
		}
	}
	return max;
}
int(*FindMaxSubArrayForce2(int array[], int start, int end))[3]
{
	int(*max)[3] = (int(*)[3])malloc((sizeof(int)) * 3);
	(*max)[2] = array[start];
	int sum ;
	for (int i = start; i <= end; i++)
	{
		for (int j = i; j <= end; j++)
		{
			sum = 0;
			for (int k = i; k <= j; k++)
			{
				sum += array[k];
			}
			if (sum > (*max)[2])
			{
				(*max)[2] = sum;
				(*max)[0] = i;
				(*max)[1] = j;
			}
		}
	}
	return max;
}
//练习4.1 - 5 
/*
	思想：由左至右处理，记录目前为止已经处理过的最大子数组，若已知A【1。。j】的最大子数组，
	A【1.。J+1】的最大子数组要么是已知的A【1。。j】的最大子数组，要么是某个右边界为j+1的某个
	子数组。
*/


int(*FindMaxSubArrayLoop(int array[], int start, int end))[3]
{
	int(*max)[3] = (int(*)[3])malloc((sizeof(int)) * 3);
	int left,sum;
	int temp_max;
	(*max)[0] = start;
	(*max)[1] = start;
	(*max)[2] = array[start];
	for (int i = start; i < end; i++)
	{
		sum = 0;
		temp_max = array[i + 1];
		left = i + 1;
		for (int j = i+1; j >= start; j--)
		{
			sum += array[j];
			if (sum > temp_max)
			{
				temp_max = sum;
				left = j;
			}
		}
		if (temp_max > (*max)[2])
		{
			(*max)[0] = left;
			(*max)[1] = i + 1;
			(*max)[2] = temp_max;	
		}
	}
	return max;
}

//获取最大子串简单测试
void FindMaxSubArrayTest()
{
	int a[] = { 13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7 };
	int(*val)[3] = FindMaxSubArray(a, 0, 14);
	free(val);
}
/*
	练习4.1-1 返回数组中最大的一个负数

	练习4.1-4 判断子数组的大小如果小于0，则返回空子数组

*/