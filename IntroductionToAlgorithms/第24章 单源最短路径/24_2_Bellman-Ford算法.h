#pragma once
#include "松弛操作.h"

void BellmanFord(LGraph *graph, int s)
{
	InitializeSingleSource(graph, s);
	for (int i = 1; i < graph->vexnum; i++)
	{
		for (int i = 1; i <= graph->vexnum; i++)
		{
			ENode *edge = graph->vexs[i]->first_edge;
			while (edge!=NULL)
			{
				Relax(graph, i, edge->ivex);
				edge = edge->next_edge;
			}

		}
	}

		//未设置负值，所以不判断

}

void Test()
{
	int msg[5][10] =
	{
		0,3,0,5,0,0,0,0,0,0,
		0,0,6,2,0,0,0,0,0,0,
		0,0,0,0,2,0,0,0,0,0,
		0,1,4,0,6,0,0,0,0,0,
		3,0,7,0,0,0,0,0,0,0,

	};
	LGraph *G = CreateGraph(msg, 5, 10);
	BellmanFord(G, 1);
}