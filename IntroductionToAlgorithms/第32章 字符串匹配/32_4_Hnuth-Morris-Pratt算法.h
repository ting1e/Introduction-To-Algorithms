#pragma once
#include "..//base.h"

void ComputePrefixFunction(int pi[], char p[], int m)
{
	pi[0] = 0;
	int k = 0;
	for (int i = 1; i < m; i++)
	{
		while (k > 0 && p[k] != p[i])
		{
			k = pi[k];
		}
		if (p[k] == p[i])
		{
			k++;
		}
		pi[i] = k;
	}
}

int KMPMatcher(char st[], int n, char sp[], int m)
{
	int *pi = (int *)malloc(sizeof(int)*m);
	ComputePrefixFunction(pi, sp, m);
	int q = 0;
	for (int i = 0; i < n; i ++ )
	{
		while (q > 0 && sp[q] != st[i])  //not match
		{
			q = pi[q-1];
		}
		if (sp[q] == st[i])
		{
			q++;
		}
		if (q == m)
		{
			return i-m+1;
		}
	}
	return -1;
}

void test()
{
	char t[] = "bacbabababacabcbab";
	char p[] = "ababaca";
	int a = KMPMatcher(t, 15, p, 7);
}