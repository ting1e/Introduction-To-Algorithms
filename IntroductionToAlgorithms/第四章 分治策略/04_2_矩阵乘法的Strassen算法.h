#pragma once
#include "..\base.h"


typedef struct MATRIX
{
	int row;	//行	有多少行
	int col;	//列	有多少列，即每行中有多少个
	int *body;
}matrix;

void FreeMatrix(matrix *m) //释放内存
{
	free(m->body);
	free(m);
}

//线性代数中简单的矩阵乘法	支持行不等于列	返回一个指针，使用完成后需要手动释放
matrix *MatrixMultiply(matrix *a,matrix *b)	
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
				*(sum->body + i * sum->col + j) +=
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
	matrix *sum = MatrixMultiply(&a, &b);
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


//将一个矩阵分成四个矩阵	内部给四个子矩阵的数组分配内存
void DepartAMatrixToFour(matrix *a,matrix *a11,matrix *a12,matrix *a21,matrix *a22)
{
	a11->row = a->row / 2, a11->col = a->col / 2;
	a11->body = (int *)malloc(sizeof(int)*a11->row*a11->col);

	a12->row = a11->row, a12->col = a->col - a11->col;
	a12->body = (int *)malloc(sizeof(int)*a12->row*a12->col);

	a21->row = a->row - a11->row, a21->col = a11->col;
	a21->body = (int *)malloc(sizeof(int)*a21->row*a21->col);

	a22->row = a->row - a11->row, a22->col = a->col - a11->col;
	a22->body = (int *)malloc(sizeof(int)*a22->row*a22->col);

	for (int i = 0; i < a->row; i++)
	{
		for (int j = 0; j < a->col; j++)
		{
			if (i < a11->row)
			{
				if (j < a11->col)
				{
					*(a11->body + i * a11->col + j) = *(a->body + i * a->col + j);
				}
				else
				{
					*(a12->body + i * a12->col + j - a11->col) = *(a->body + i * a->col + j);
				}
			}
			else
			{
				if (j < a11->col)
				{
					*(a21->body + (i - a11->row)*a21->col + j) = *(a->body + i * a->col + j);
				}
				else
				{
					*(a22->body + (i - a11->row)*a22->col + j - a11->col) = *(a->body + i * a->col + j);
				}
			}
		}
	}

}

matrix *ComhineMatrix2One(matrix *a11, matrix *a12, matrix *a21, matrix *a22)
{
	matrix *a = (matrix *)malloc(sizeof(matrix));
	a->row = a11->row + a22->row;
	a->col = a11->col + a22->col;
	a->body = (int *)malloc(sizeof(int)*a->row*a->col);

	for (int i = 0; i < a->row; i++)
	{
		for (int j = 0; j < a->col; j++)
		{
			if (i < a11->row)
			{
				if (j < a11->col)
				{
					*(a->body + i * a->col + j) = *(a11->body + i * a11->col + j);
				}
				else
				{
					*(a->body + i * a->col + j) = *(a12->body + i * a12->col + j - a11->col);
				}
			}
			else
			{
				if (j < a11->col)
				{
					*(a->body + i * a->col + j) = *(a21->body + (i - a11->row)*a21->col + j);
				}
				else
				{
					*(a->body + i * a->col + j) = *(a22->body + (i - a11->row)*a22->col + j - a11->col);
				}
			}
		}
	}
}

void DepartTest()
{
	int abody[8] = { 1,2,3,4,5,6,7,8 };
	matrix a = { 2,4,abody };
	matrix *a11, *a12, *a21, *a22;
	a11 = (matrix*)malloc(sizeof(matrix));
	a12 = (matrix*)malloc(sizeof(matrix));
	a21 = (matrix*)malloc(sizeof(matrix));
	a22 = (matrix*)malloc(sizeof(matrix));
	DepartAMatrixToFour(&a, a11, a12, a21, a22);
	int i = 0;
}

matrix *MatrixPlus(matrix *a, matrix *b)
{
	matrix *ret_val = (matrix *)malloc(sizeof(matrix));
	ret_val->body = (int *)malloc(sizeof(int)*a->row*a->col);
	ret_val->row = a->row;
	ret_val->col = a->col;
	for (int i = 0; i < a->row; i++)
	{
		for (int j = 0; j < a->col; j++)
		{
			*(ret_val->body + i * ret_val->col + j) =
				*(a->body + i * a->col + j) + *(b->body + i * b->col + j);
		}
	}
	return ret_val;
}

matrix *MatrixMinus(matrix *a, matrix *b)
{
	matrix *ret_val = (matrix *)malloc(sizeof(matrix));
	ret_val->body = (int *)malloc(sizeof(int)*a->row*a->col);
	ret_val->row = a->row;
	ret_val->col = a->col;
	for (int i = 0; i < a->row; i++)
	{
		for (int j = 0; j < a->col; j++)
		{
			*(ret_val->body + i * ret_val->col + j) =
				*(a->body + i * a->col + j) - *(b->body + i * b->col + j);
		}
	}
	return ret_val;
}


matrix *MatrixMultiplyStrassen(matrix *a, matrix *b)
{
	if (a->row == 1 && a->col == 1 && b->row == 1 && b->col == 1)
	{
		matrix *ret_val = (matrix *)malloc(sizeof(matrix));
		ret_val->row = 1;
		ret_val->col = 1;
		ret_val->body = (int *)malloc(sizeof(int)*ret_val->row*ret_val->col);
		*ret_val->body = (*a->body)*(*b->body);
		return ret_val;
	}
	else if(a->row > 1 && a->col > 1 && b->row > 1 && b->col > 1)
	{
		matrix *a11, *a12, *a21, *a22;
		a11 = (matrix*)malloc(sizeof(matrix));
		a12 = (matrix*)malloc(sizeof(matrix));
		a21 = (matrix*)malloc(sizeof(matrix));
		a22 = (matrix*)malloc(sizeof(matrix));
		DepartAMatrixToFour(a, a11, a12, a21, a22);

		matrix *b11, *b12, *b21, *b22;
		b11 = (matrix*)malloc(sizeof(matrix));
		b12 = (matrix*)malloc(sizeof(matrix));
		b21 = (matrix*)malloc(sizeof(matrix));
		b22 = (matrix*)malloc(sizeof(matrix));
		DepartAMatrixToFour(b, b11, b12, b21, b22);

		matrix *s1 = MatrixMinus(b12,b22);
		matrix *s2 = MatrixPlus(a11, a12);
		matrix *s3 = MatrixPlus(a21, a22);
		matrix *s4 = MatrixMinus(b21, b11);
		matrix *s5 = MatrixPlus(a11, a22);
		matrix *s6 = MatrixPlus(b11, b22);
		matrix *s7 = MatrixMinus(a12, a22);
		matrix *s8 = MatrixPlus(b21, b22);
		matrix *s9 = MatrixMinus(a11, a21);
		matrix *s10 = MatrixPlus(b11, b12);

		matrix *p1 = MatrixMultiplyStrassen(a11, s1);
		matrix *p2 = MatrixMultiplyStrassen(s2, b22);
		matrix *p3 = MatrixMultiplyStrassen(s3, b11);
		matrix *p4 = MatrixMultiplyStrassen(a22, s4);
		matrix *p5 = MatrixMultiplyStrassen(s5, s6);
		matrix *p6 = MatrixMultiplyStrassen(s7, s8);
		matrix *p7 = MatrixMultiplyStrassen(s9, s10);

		matrix *tmp1 = MatrixPlus(p5, p4);
		matrix *tmp2 = MatrixMinus(p2, p6);
		matrix *c11 = MatrixMinus(tmp1, tmp2);

		matrix *c12 = MatrixPlus(p1, p2);

		matrix *c21 = MatrixPlus(p3, p4);
		
		matrix *tmp3 = MatrixPlus(p1, p5);
		matrix *tmp4 = MatrixPlus(p3, p7);
		matrix *c22 = MatrixMinus(tmp3, tmp4);


		matrix *ret_val = ComhineMatrix2One(c11, c12, c21, c22);

		FreeMatrix(a11); FreeMatrix(a12); FreeMatrix(a21); FreeMatrix(a22);
		FreeMatrix(b11); FreeMatrix(b12); FreeMatrix(b21); FreeMatrix(b22);
		FreeMatrix(s1); FreeMatrix(s2); FreeMatrix(s3); FreeMatrix(s4); FreeMatrix(s5);
		FreeMatrix(s6); FreeMatrix(s7); FreeMatrix(s8); FreeMatrix(s9); FreeMatrix(s10);
		FreeMatrix(p1); FreeMatrix(p2); FreeMatrix(p3); FreeMatrix(p4); FreeMatrix(p5);
		FreeMatrix(p6); FreeMatrix(p7);
		FreeMatrix(tmp1); FreeMatrix(tmp2); FreeMatrix(tmp3); FreeMatrix(tmp4);
		FreeMatrix(c11); FreeMatrix(c12); FreeMatrix(c21); FreeMatrix(c22);
		return ret_val;
	}
	else
	{
		return MatrixMultiply(a, b);
	}
}

void MutiplyStrassenTest()
{
	int abody[] = { 1,2,3,4 };
	int bdody[] = { 5,6,7,8 };
	matrix a = { 2,2,abody };
	matrix b = { 2,2,bdody };
	matrix *sum = MatrixMultiplyStrassen(&a, &b);
	printf("%d", (int)(*(sum->body + 1 * sum->col + 1)));
	int i = 0;
}


/*
	练习4.2-3 适应n不是2的幂的情况
	先找出最大的n的幂次方的子矩阵，然后利用矩阵运算的知识进行运算。
	等什么时候复习了线性代数的知识在来写代码吧！！！  嘤嘤嘤
	练习4.2-3
	a,b,c,d	三次乘法得到（ac-bd）+（ad+bc）
	1.x=(a+b)(c+d)=ac+bd+ad+bc	
	2.y=ac	
	3.z=bd

	ac-bd=y-z
	ad+bc=x-y-z
*/
