#pragma once
#include "..\base.h"
#include "12_3_插入和删除.h"

void test()
{
	int a[10]={15,6,18,3,13,17,20,2,4,7};
	BSTree *root =BuildTree(NULL,a,0,10);
	InorderTreeWalk(root);
	printf("\n");

	InorderNoRecursion(root);

	printf("\n");
	TreeInsert(&root,30);
	TreeInsert(&root,1);
	InorderTreeWalk(root);
	printf("\n");

	TreeDelete(&root,1);
	TreeDelete(&root,3);
	TreeDelete(&root,20);
	TreeDelete(&root,30);
	InorderTreeWalk(root);
	printf("\n");
	
	MyTreeInsert(&root,NULL,1);
	MyTreeInsert(&root,NULL,3);
	MyTreeInsert(&root,NULL,30);
	InorderTreeWalk(root);
	printf("\n");

}
