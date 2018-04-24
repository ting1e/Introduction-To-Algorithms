#pragma once
#include "..\base.h"

//除法散列函数

int DivideHash(int k)
{
	return k%701;
}

//乘法散列函数
// 	h(k)=(m*(kA mod 1))
//
//
int MultHash(int k)
{
	int m=2<<10;
	return (int)((double)k*0.618034)*m;
}
