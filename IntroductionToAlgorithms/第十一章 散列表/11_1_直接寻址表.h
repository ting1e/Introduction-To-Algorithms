#pragma once
#include "..\base.h"
// 散列表

#define SIZE 100
#define ((x).key) (x)


int t[SIZE];

int DirectAddressSearch(int t[],int k)
{
	return t[k];
}

void DirectAddressInsert(int t[],int x)
{
	t[x.key]=x;
}

/*
 *注意本章所有均未测试。。。。。。 	 	
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
