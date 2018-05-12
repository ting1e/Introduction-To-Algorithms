#pragma once
#include "..//base.h"

int NaiveStringMatcher(char t[], int n, char p[], int m)
{
	int i, j;
	for (i = 0; i < n - m; i++)
	{
		int flag = 0;
		for (j = 0; j < m; j++)
		{
			if (t[i + j] == p[j])
			{
				flag++;
			}
		}
		if (flag == m)
			break;
	}
	return i;
}

void test()
{
	char t[] = "acaabc";
	char p[] = "aab";
	int a = NaiveStringMatcher(t, 6, p, 3);
}