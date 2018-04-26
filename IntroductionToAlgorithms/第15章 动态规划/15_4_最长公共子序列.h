#include "..//base.h"

#define SIZE 100

// ↖ ：11   ↑：12  ←：9 

void PrintLCS(int b[][SIZE], char x[], int i, int j)
{
	if (i == 0 || j == 0)
	{
		return;
	}
	if (b[i][j] == 11)
	{
		PrintLCS(b, x, i - 1, j - 1);
		printf("%c ", x[i]);
	}
	else if (b[i][j] == 12)
	{
		PrintLCS(b, x, i - 1, j);
	}
	else
	{
		PrintLCS(b, x, i, j - 1);
	}
}

//练习 15.4-2

void PrintLCS_(int c[][SIZE], char x[], char y[], int i, int j)
{
	if (i == 0 || j == 0)
		return;
	if (x[i] == y[j])
	{
		PrintLCS_(c, x, y, i - 1, j - 1);
		printf("%c ", x[i]);
	}
	else if (c[i - 1][j] >= c[i][j - 1])
	{
		PrintLCS_(c, x, y, i - 1, j);
	}
	else
	{
		PrintLCS_(c, x, y, i, j - 1);
	}
}


void LCSLength(char x[], char y[], int x_length, int y_length)
{
	int b[SIZE][SIZE] = { 0 };
	int c[SIZE][SIZE] = { 0 };
	for (int i = 1; i <= x_length ; i++)
	{
		for (int j = 1; j <= y_length; j++)
		{
			if (x[i] == y[j])
			{
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = 11;
			}
			else if (c[i - 1][j] >= c[i][j - 1])
			{
				c[i][j] = c[i - 1][j];
				b[i][j] = 12;
			}
			else
			{
				c[i][j] = c[i][j - 1];
				b[i][j] = 9;
			}
		}
	}
	PrintLCS(b, x, x_length, y_length);
	printf("\n");
	PrintLCS_(c, x, y, x_length, y_length);

}

//联系15.4-3
void __MyLCSLength(int c[][SIZE], char x[], char y[], int i, int j)
{
	if (i == 0 || j == 0)
		return;
	if (c[i][j] != 0)
		return;
	if (x[i] == y[j])
	{
		__MyLCSLength(c, x, y, i - 1, j - 1);
		c[i][j] = c[i - 1][j - 1] + 1;
	}
	else 
	{
		__MyLCSLength(c, x, y, i - 1, j);
		__MyLCSLength(c, x, y, i, j - 1);
		if (c[i - 1][j] >= c[i][j - 1])
		{
			c[i][j] = c[i - 1][j];
		}
		else
		{
			c[i][j] = c[i][j - 1];
		}
			
	}

}
void MyLCSLength(char x[], char y[], int x_length, int y_length)
{
	int c[SIZE][SIZE] = {0};
	__MyLCSLength(c, x, y, x_length, y_length);
	PrintLCS_(c, x, y, x_length, y_length);

}

/*
	练习15.4-5  
	1  对数组进行排序  然后与原数组lcs
	2  如下	   原数组x[0-n] 
	思路：c[0-n]  c[i] 表示0-i中以x[i]结尾的最长递增子数组   

*/



void UpLongest(int x[], int size)
{
	int c[100] = { 1 };
	for (int i = 1; i < size; i++)
	{
		c[i] = 1;
		for (int j = 0; j < i; j++)
		{
			if (x[i] > x[j])
			{
				c[i] = MAX(c[j] + 1, c[i]);
			}
		}
	}

}



void test()
{
	char x[] = { '0','a','b','c','b','d','a','b' };
	char y[] = { '0','b','d','c','a','b','a' };
	LCSLength(x, y, 7, 6);
	printf("\n");
	MyLCSLength(x, y, 7, 6);

	int c[] = { 3,2,1,4,5,9,10,7,8,11 };
	UpLongest(c, 10);
}