
#pragma once
#include "22_1_图的表示.h"

//深度优先遍历，一条道走到黑。

void DFSVisit(LGraph *G, VNode* u, int *time)
{
	(*time)++;
	u->d = *time;
	u->color = gray;
	ENode *edge = u->first_edge;
	printf("%c ", u->data);
	while (edge!=NULL)
	{
		if (G->vexs[edge->ivex]->color == white)
		{
			G->vexs[edge->ivex]->pre = u;
			DFSVisit(G, G->vexs[edge->ivex], time);
		}
		edge = edge->next_edge;
	}
	u->color = black;
	(*time)++;
	u->f = *time;
}



void DFS(LGraph * G)
{
	for (int i = 0; i < G->vexnum; i++)
	{
		G->vexs[i]->color = white;
		G->vexs[i]->pre = NULL;
	}
	int time = 0;
	for (int i = 0; i < G->vexnum; i++)
	{
		if (G->vexs[i]->color == white)
		{
			DFSVisit(G, G->vexs[i], &time);
		}
	}

}

void test()
{
	/*
	r  --  s      t  --  u
	|      |   /  |   /  |
	v      w  --  x  --  y

	s 开始。
	*/


}
