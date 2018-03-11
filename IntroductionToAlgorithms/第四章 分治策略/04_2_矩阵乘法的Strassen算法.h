#pragma once
#include "..\bash.h"

typedef struct MATRIX
{
	int row;	//行
	int col;	//列
	int *body;
}matrix;

void FreeMatrix(matrix *m)
{
	free(m->body);
	free(m);
}

//线性代数中简单的矩阵乘法
matrix *SquareMatrixMultiply(matrix *a,matrix *b)
{
	matrix *sum = (matrix *)malloc(sizeof(matrix));
	sum->row = a->row;
	sum->col = b->col;
	sum->body = (int *)malloc(sizeof(int)*sum->row*sum->col);

	for (int i = 0; i < a->row; i++)
	{
		for (int j = 0; j < b->col; j++)
		{
			*(sum->body + i * sum->col + j) = 0;
			for (int k = 0; k < a->col; k++)
			{
				*(sum->body + i * sum->row + j) +=
					(int)(*(a->body + i * a->col + k))* (int)(*(b->body + k * b->col + j));
			}
		}
	}
	return sum;
}

void MutiTest()
{
	int abody[8] = { 1,1,1,1,2,2,2,2 };
	int bdody[8] = { 3,4,3,4,3,4,3,4 };
	matrix a = { 2,4,abody };
	matrix b = { 4,2,bdody };
	matrix *sum = SquareMatrixMultiply(&a, &b);
	printf("%d", (int)(*(sum->body + 1*sum->col+1)));
	int i = 0;
}

/*
	矩阵乘法 Strassen算法。
	算法概述：
	1.将矩阵分解成（n/2）*(n/2）个子矩阵
	2.创建10个矩阵
	S1=B12-B22	S2=A11+A12	S3=A21+A22	S4=B21-B11	S5=A11+A22
	S6=B11+B22	S7=A12-A22	S8=B21+B22	S9=A11-A21	S10=B11+B12
	3.递归的计算7次（n/2）*(n/2）矩阵的乘法
	P1=A11*S1	P2=S2*B22	P3=S3*B11	P4=A22*S4	
	P5=S5*S6	P6=S7*S8	P7=S9*S10
	4.加减法运算得出4个子矩阵
	C11=P5+P4-P2+P6		C12=P1+P2	C21=P3+P4	C22=P5+P1-P4-P2
	*/

matrix *SquareMatrixMultiplyStrassen(matrix a, matrix b)
{
	if (a.row == 1 && a.col == 1 && b.row == 1 && b.col == 1)
	{
		matrix *ret_val = (matrix *)malloc(sizeof(matrix));
		ret_val->row = 1;
		ret_val->col = 1;
		ret_val->body = (int *)malloc(sizeof(int)*ret_val->row*ret_val->col);
		*ret_val->body = (*a.body)*(*b.body);
		return ret_val;
	}
	else
	{

	}
}