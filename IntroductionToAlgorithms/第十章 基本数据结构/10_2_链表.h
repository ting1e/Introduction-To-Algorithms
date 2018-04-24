#pragma once
#include "..\base.h"
//双向链表、、 
//前面几种都是简单的双向链表
//
typedef struct LIST
{
	int key;
	struct LIST *prev;
	struct LIST *next;
} LinkList;

LinkList *ListSearch(LinkList *l,int k)
{
	while(l!=NULL&&l->key!=k )
	{
		l=l->next;
	}
	return l;
}

int ListInsert(LinkList **l,int x)
{
	if(*l==NULL)
	{
		return 0;
	}
	LinkList * new_node = (LinkList *)malloc(sizeof(LinkList));
	
	new_node->key=x;
	new_node->prev=NULL;
	new_node->next = *l;
	(*l)->prev=new_node;
	*l=new_node;
	return 1;
}
int ListDelete(LinkList **l,int x)
{
	LinkList *temp =*l;
	while(temp!=NULL&&temp->key!=x);
	if(temp==NULL)
	{
		return 0;
	}
	else
	{
		temp->next->prev=temp->prev;
		temp->prev->next=temp->next;
		free(temp);
		return 1;
	}
}










