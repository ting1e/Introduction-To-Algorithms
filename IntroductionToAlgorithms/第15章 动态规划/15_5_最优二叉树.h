#pragma once
#include "..//base.h"

void OptimalBST(double p[], double q[], int n)
{
	double e[10][10], w[10][10];
	int  root[10][10];
	for (int i = 1; i <= n + 1; i++)
	{
		e[i][i - 1] = q[i - 1];
		w[i][i - 1] = q[i - 1];
	}
	for (int l = 1; l <= n; l++)
	{
		for (int i = 1; i <= n - l + 1; i++)
		{
			int j = i + l - 1;
			e[i][j] = 100;
			w[i][j] = w[i][j-1] + q[j] + p[j];
			for (int r = i; r <= j; r++)
			{
				double t = e[i][r - 1] + e[r + 1][j] + w[i][j];
				if (t < e[i][j])
				{
					e[i][j] = t;
					root[i][j] = r;
				}
			}
		}
	}

	int x;

}

void test()
{
	double p[] = { 0,0.15,0.10,0.05,0.10,0.20 };
	double q[] = { 0.05,0.10,0.05,0.05,0.05,0.10 };
	OptimalBST(p, q, 5);
}