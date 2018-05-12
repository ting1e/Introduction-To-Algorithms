#pragma once
#include "..//base.h"


int pow(int x, int y)
{
	int r = 1;
	while (y--)
	{
		r *= x;
	}
	return r;
}


int RabinKarpMatcher(char st[], int n, char sp[], int m, int d, int q)
{
	int i, j;
	int p = 0, t = 0;
	int h = pow(d, m - 1) % q;
	for (i = 0; i < m; i++)
	{
		p = (d*p +sp[i]) % q;
		t = (d*t + st[i]) % q;
	}
	for (int i = 0; i < n - m; i++)
	{
		if (p == t)
		{
			int flag = 0;
			for (j = 0; j < m; j++)
			{
				if (st[i + j] == sp[j])
				{
					flag++;
				}
			}
			if (flag == m)
				break;
		}
		if (i < n - m)
		{
			t = (d*(t - st[i] * h) + st[i + m]) % q;
		}
	}
	return i;
}


void test()
{
	char t[] = "acaabc";
	char p[] = "aab";
	int a = RabinKarpMatcher(t, 6, p, 3,10,13);
}