
#pragma once
#include "22_1_图的表示.h"

//深度优先遍历，一条道走到黑。

void DFSVisit(LGraph *G, int u, int *time)
{
	(*time)++;
	G->vexs[u]->d = *time;
	G->vexs[u]->color = gray;
	ENode *edge = G->vexs[u]->first_edge;
	printf("%c ", G->vexs[u]->data);
	while (edge!=NULL)
	{
		if (G->vexs[edge->ivex]->color == white)
		{
			G->vexs[edge->ivex]->pre = u;
			DFSVisit(G, edge->ivex, time);
		}
		edge = edge->next_edge;
	}
	G->vexs[u]->color = black;
	(*time)++;
	G->vexs[u]->f = *time;
}



void DFS(LGraph * G)
{
	for (int i = 1; i <= G->vexnum; i++)
	{
		G->vexs[i]->color = white;
		G->vexs[i]->pre = 0;
	}
	int time = 0;
	for (int i = 1; i <= G->vexnum; i++)
	{
		if (G->vexs[i]->color == white)
		{
			DFSVisit(G, i, &time);
		}
	}

}

void _test()
{
	/*
	r  --  s      t  --  u
	|      |   /  |   /  |
	v      w  --  x  --  y

	s 开始。
	*/


}
