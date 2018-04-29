#pragma once
#include "..//base.h"

#ifndef TYPE
	#define TYPE int 
#endif // !TYPE


struct Stack
{
	int ele[SIZE];
	int top;
};

void InitStack(struct Stack *S)
{
	S->top=-1;
}


int StackEmpty(struct Stack *S)
{
	return S->top==-1;
}

int Push(struct Stack *S,int x)
{
	if(S->top>=50&&S->top<-1)
	{
		return 0;
	}
	else
	{
		S->ele[++S->top]=x;
		return 1;
	}
		
}

int Pop(struct Stack *S,int *x)
{
	if(StackEmpty(S))
	{
		return 0;
	}
	else
	{
		*x=S->ele[S->top];
		S->top--;
		return 1;
	}
}

void StackTest()
{
	int a=10,b=20,c;
	struct Stack S;
	InitStack(&S);
	Push(&S,11);
	Push(&S,51);
	Pop(&S,&a);
	Pop(&S,&b);
	printf("%d\n",a);
	Pop(&S,&c);
	printf("%d  %d  %d ",a,b,c);
}

struct Queue
{
	TYPE ele[SIZE];
	int head;
	int tail;
};
void InitQueue(struct Queue *Q)
{
	Q->head=0;
	Q->tail=0;
}

int EnQueue(struct Queue *Q, TYPE x)  	//可以处理上溢和下溢出
{
	if((Q->tail+1)%(SIZE-1)==Q->head)
	{
		return 0;
	}
	else
	{
		Q->ele[Q->tail++]=x;
		if(Q->tail>=SIZE)
		{
			Q->tail=0;
		}
		return 1;
	}
}

int DeQueue(struct Queue *Q, TYPE *x)
{
	if(Q->head==Q->tail)
	{
		return 0;
	}
	else
	{
		*x=Q->ele[Q->head++];
		if(Q->head>=SIZE)
		{
			Q->head=0;
		}
		return 1;
	}
}
// 练习10.1-5 	下面两个加上上面两个。
int EnQueueHead(struct Queue *Q, TYPE x)
{
	if((Q->tail+1)%(SIZE-1)==Q->head)
	{
		return 0;
	}
	else
	{
		Q->ele[--Q->head]=x;
		if(Q->head<0)
		{
			Q->head=SIZE-1;
		}
		return 1;
	}
}

int DeQueueTail(struct Queue *Q, TYPE *x)
{
	if(Q->head==Q->tail)
	{
		return 0;
	}
	else
	{
		*x=Q->ele[--Q->tail];
		if(Q->tail<0)
		{
			Q->tail=SIZE-1;
		}
		return 1;
	}
}


/*
void QueueTest()
{
	struct Queue Q;
	TYPE x;
	TYPE i=1;
	InitQueue(&Q);
	while(EnQueue(&Q,i))
	{
		i++;
	}
	DeQueue(&Q,&x);
	DeQueue(&Q,&x);
	DeQueue(&Q,&x);
	while(EnQueue(&Q,i))
	{
		i++;
	}
	while(DeQueue(&Q,&x))
	{
		printf("%d\n",x);
	}
	
}
*/

/*
	练习10.1-2 分别以1和n为栈底，从两侧向中心生长。
	
	练习10.1-7
	
	两个栈S1，S2  
		Depend on the operation
	EnQueue(x)		//θ(1)
		S1.Push(x)
		
	Dequeue(x)			  //O(n)	I am not sure about the low boundary.
							//Guess e[X]==θ(1)
		if  S2 is empty
			S2.Push(all S1) 
		else
			S2.Pop
		
		
		
	练习10.1-8
	Q1,Q2 	//let Q1,Q2 circle maybe a good choice 
	Push(x)				//θ(1)
		Q1.EnQueue(x)
		
	Pop 		//θ(n)
		Q2.EnQueue(all Q1) and record last one 
		Q1.EnQueue(all Q2 expect last one )
		return Q2.Dequeue
		

	*/
