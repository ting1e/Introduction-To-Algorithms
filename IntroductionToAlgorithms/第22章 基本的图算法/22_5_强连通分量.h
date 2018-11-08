#pragma once

#include "22_1_图的表示.h"
#include "22_3_深度优先搜索.h"



/*

	算法流程：
	1.深度优先遍历G,算出每个结点u的结束时间f[u],起点如何选择无所谓。

	2.深度优先遍历G的转置图G T ,选择遍历的起点时,按照结点的结束时间从大到小进行。遍历的过程中,一边遍历,
	一边给结点做分类标记,每找到一个新的起点,分类标记值就加1。
*/

void StronglyDFSVisit(LGraph *G, VNode* u, int *time,int c)
{
	(*time)++;
	u->d = *time;
	u->color = gray;
	u->cla = c;
	ENode *edge = u->first_edge;
	printf("%c ", u->data);
	while (edge != NULL)
	{
		if (G->vexs[edge->ivex]->color == white)
		{
			G->vexs[edge->ivex]->pre = u;
			StronglyDFSVisit(G, &G->vexs[edge->ivex], time,c);
		}
		edge = edge->next_edge;
	}
	u->color = black;
	(*time)++;
	u->f = *time;
}



void StronglyDFS(LGraph * G)
{
	VNode *sort[SIZE] = { 0 };
	int class = 1;
	for (int i = 0; i < G->vexnum; i++)
	{
		G->vexs[i]->color = white;
		G->vexs[i]->pre = NULL;
		sort[G->vexs[i]->f] = G->vexs[i];
	}
	int time = 0;
	for (int i = SIZE-1; i >=0; i--)
	{
		if(sort[i]!=NULL&& (*sort[i]).color == white)
		{
			StronglyDFSVisit(G, sort[i], &time,class++);
			
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



void test1()
{
	
	int msg[8][10];
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 10; j++)
			msg[i][j] = -1;
	msg[0][0] = 1;

	msg[1][0] = 2;
	msg[1][1] = 4;
	msg[1][2] = 5;

	msg[2][0] = 3;
	msg[2][1] = 6;

	msg[3][2] = 2;
	msg[3][1] = 7;

	msg[4][0] = 0;
	msg[4][1] = 5;

	msg[5][0] = 6;
	
	msg[6][0] = 5;
	msg[6][1] = 7;

	msg[7][0] = 7;

	LGraph *G = CreateGraph(msg, 8, 14);
	
	LGraph *GT = StronglyConnectedComponents(G);

	printf("\n");
	free(G);
	free(GT);

}