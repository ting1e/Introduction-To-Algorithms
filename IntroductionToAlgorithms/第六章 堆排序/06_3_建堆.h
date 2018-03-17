#pragma once
#include "..\base.h"
#include "06_1_堆_2_堆的性质.h"

/*
	建立最大堆： n/2 。。。。。。n 都是叶节点
	对树中的每一个节点调用MaxHeapify
*/

void BuildMaxHeap(int a[], int length)
{
	for (int i = length / 2; i > 0; i--)
	{
		MaxHeapify_(a, i, length);
	}
}

void BuildTest()
{
	int a[] = { 0,4,1,3,2,16,9,10,14,8,7 };
	BuildMaxHeap(a, 10);
}

/*	
	练习6.3-2  因为MaxHeapify函数的假定根节点的二叉树都是最大堆。
	如果从1开始，他的两个子节点上的指可能不是最大值。然后程序就结束了。所以对于i来说
	必须递减。
*/