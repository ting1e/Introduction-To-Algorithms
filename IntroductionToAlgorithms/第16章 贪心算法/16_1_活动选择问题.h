#pragma once
#include "..//base.h"

void RecursizeActivitySelector(int start[], int end[], int k,int n, int ret[], int current)
{
	int m = k + 1;
	while (m <= n && start[m] < end[k])
	{
		m++;
	}
	if (m <= n)
	{
		ret[current] = m;
		RecursizeActivitySelector(start, end, m, n, ret, current + 1);
	}
}

void GreedyActivitySelector(int s[], int f[],int n,int ret[])
{
	int cur = 0;
	int k = 1;
	ret[cur++] = 1;
	for (int m = 2; m <= n; m++)
	{
		if (s[m] > f[k])
		{
			ret[cur++] = m;
			k = m;
		}
	}
}




/*
	练习16.1-1

	for i <- 0 to n+1
	  do c[i,i] <- 0
		for l <- 1 to n+1
		   do for i <- 0 to n+1-l
			    do j <- i+l
					c[i,j] <- 0
					for k <- i+1 to j-1
						do if f_i <= s_k and f_k <= s_j  // test if activity a_k is in S_{ij}
							then q <- c[i,k] + c[k,j] + 1
																						                       if q > c[i,j]																							                        then c[i,j] <- q
																																	                          a[i,j] <- k
*/


void test()
{
	int s[] = { 0,1,3,0,5,3,5,6,8,8,2,12 };
	int f[] = { 0,4,5,6,7,9,9,10,11,12,14,16 };
	int ret[10] = { 0 };
	RecursizeActivitySelector(s,f,0,11,ret,0);
	int ret2[10] = { 0 };
	GreedyActivitySelector(s, f, 11, ret2);


}