#pragma once

#include "22_1_图的表示.h"
#include "22_3_深度优先搜索.h"



/*

	算法流程：
	1.深度优先遍历G,算出每个结点u的结束时间f[u],起点如何选择无所谓。

	2.深度优先遍历G的转置图G T ,选择遍历的起点时,按照结点的结束时间从大到小进行。遍历的过程中,一边遍历,
	一边给结点做分类标记,每找到一个新的起点,分类标记值就加1。
*/

void StronglyDFSVisit(LGraph *G, int u, int *time,int c)
{
	(*time)++;
	G->vexs[u]->d = *time;
	G->vexs[u]->color = gray;
	G->vexs[u]->category = c;
	ENode *edge = G->vexs[u]->first_edge;
	printf("%c ", G->vexs[u]->data);
	while (edge != NULL)
	{
		if (G->vexs[edge->ivex]->color == white)
		{
			G->vexs[edge->ivex]->pre = u;
			StronglyDFSVisit(G, edge->ivex, time,c);
		}
		edge = edge->next_edge;
	}
	G->vexs[u]->color = black;
	(*time)++;
	G->vexs[u]->f = *time;
}



void StronglyDFS(LGraph * G)
{
	VNode *sort[SIZE] = { 0 };
	int category = 1;
	for (int i = 1; i <= G->vexnum; i++)
	{
		G->vexs[i]->color = white;
		G->vexs[i]->pre = 0;
		sort[G->vexs[i]->f] = G->vexs[i];
	}
	int time = 0;
	for (int i = SIZE-1; i >=0; i--)
	{
		if(sort[i]!=NULL&& sort[i]->color == white)
		{
			StronglyDFSVisit(G, i, &time,category++);
		}
	}

}



LGraph *StronglyConnectedComponents(LGraph *G)
{
	DFS(G);
	LGraph *GT = TransposeGraph(G);
	StronglyDFS(GT);
	return GT;
}



void test()
{
	

	int msg[8][10] =
	{
		2,0,0,0,0,0,0,0,0,0,
		3,5,6,0,0,0,0,0,0,0,
		4,7,0,0,0,0,0,0,0,0,
		3,8,0,0,0,0,0,0,0,0,
		1,6,0,0,0,0,0,0,0,0,

		7,0,0,0,0,0,0,0,0,0,
		6,8,0,0,0,0,0,0,0,0,
		8,0,0,0,0,0,0,0,0,0,
	};

	LGraph *G = CreateGraph(msg, 8, 14);
	
	LGraph *GT = StronglyConnectedComponents(G);

	printf("\n");
	DestroyGraph(G);
	DestroyGraph(GT);

}