#pragma once
#include "..//base.h"

/*
	Á·Ï°16.2-2   0-1±³°üÎÊÌâ

*/

int MaxValue(int v[], int w[], int i, int sum_weight)
{
	if (i == 0 || sum_weight == 0)
		return 0;
	else
	{
		if (w[i] <= sum_weight)
		{
			return MAX(MaxValue(v, w, i - 1, sum_weight - w[i])+v[i], MaxValue(v, w, i - 1, sum_weight));
		}
		else
		{
			return MaxValue(v, w, i - 1, sum_weight);
		}

	}
}

int MaxValue1(int v[], int w[], int n,int weight)
{
	int c[100][100] = { 0 };
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= weight; j++)
		{
			if (w[i] <= j)
			{
				c[i][j] = MAX(c[i - 1][j - w[i]] + v[i], c[i - 1][j]);
			}
			else
			{
				c[i][j] = c[i - 1][weight];
			}
		}
	}
	return c[n][weight];

}

void test()
{
	int w[] = { 0,10,20,30 };
	int v[] = { 0,60,100,120 };

	int x = MaxValue(v, w, 3, 50);
	int y = MaxValue1(v, w, 3, 50);
}