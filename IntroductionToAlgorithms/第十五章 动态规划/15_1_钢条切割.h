#include "..//base.h"

//递归求解
int CutRod(int p[],int n)
{
	if(n==0)
		return 0;
	int q=-1;
	int i;
	for(i=1;i<=n;i++)
	{
		q=MAX(q,p[i]+CutRod(p,n-i));
	}
	return q;
}

//自顶向上方法   备忘录
int MemorizedCutRodAux(int p[],int n,int r[])
{
	if(r[n]>=0)
		return r[n];
	int q=-1;
	if(n==0)
		q=0;
	else
	{
		int i;
		for(i=1;i<=n;i++)
		{
			q=MAX(q,p[i]+MemorizedCutRodAux(p,n-i,r));
		}
	}
	r[n]=q;
	return q;
}

int MemoizedCutRod(int p[],int n)
{
	int i;
	int r[100];
	for(i=0;i<=n;i++)
	{
		r[i]=-1;
	}
	return MemorizedCutRodAux(p,n,r);
}


//自底向上方法
//
int BottomUpRod(int p[],int n)
{
	int r[100]={0}; //因不支持变长数组，简单的以合适大小的数组表示。
	int i,j,q;
	for(i=1;i<=n;i++)
	{
		q=-1;
		for(j=1;j<=i;j++)
		{
			q=MAX(q,p[j]+r[i-j]);
		}
		r[i]=q;
	}
	return r[n];
}


//给出对应切割长度
//
int *ExtendedBottomUpCutRod(int p[],int n,int *t)
{
	int *s=(int *)malloc(sizeof(int)*(n+1));
	int r[100]={0};
	int i,j,q;
	for(i=1;i<=n;i++)
	{
		q=-1;
		for(j=1;j<=i;j++)
		{
			if(q<p[j]+r[i-j])
			{
				q=p[j]+r[i-j];
				s[i]=j;
				r[i]=q;
			}
		}
	}
	*t=r[n];
	return s;
}
//打印
void PrintCutRodSolution(int p[],int n)
{
	int r;
	int *s=ExtendedBottomUpCutRod(p,n,&r);
	printf("%d : piece %d \n",n,r);
	while(n>0)
	{
		printf("%d   ",*(s+n));
		n=n-s[n];
	}
	printf("\n");
}



void test()
{
	int p[] = { 0,1,5,8,9,10,17,17,20,24,30 };
	int pi;
	pi = CutRod(p,10);
	printf("10: price %d\n ",pi);

	pi = MemoizedCutRod(p,10);
	printf("10: price %d\n ",pi);

	pi = BottomUpRod(p,10);
	printf("10: price %d\n ",pi);


	PrintCutRodSolution(p,9);
}
