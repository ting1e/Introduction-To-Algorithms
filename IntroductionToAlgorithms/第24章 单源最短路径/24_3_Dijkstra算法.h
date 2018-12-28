#pragma once
#include "ËÉ³Ú²Ù×÷.h"

#define IN_S 50

int ExactMin(LGraph *graph)
{
	int min_node = 0;
	int min = INT_MAX;
	for (int i = 1; i <= graph->vexnum; i++)
	{
		if (graph->vexs[i]->category != IN_S)
		{
			if (graph->vexs[i]->d < min)
			{
				min = graph->vexs[i]->d;
				min_node = i;
			}
		}
	}
	if (min_node == 0)
		return 0;
	graph->vexs[min_node]->category = IN_S;
	return min_node;
}


void Dijkstra(LGraph *graph, int source)
{
	InitializeSingleSource(graph, source);

	graph->vexs[source]->category = IN_S;
	ENode *edge = graph->vexs[source]->first_edge;
	while (edge != NULL)
	{
		Relax(graph, source, edge->ivex);
		edge = edge->next_edge;
	}

	for (int i = 0; i < graph->vexnum - 1; i++)
	{
		int u = ExactMin(graph);
		if (u == 0)
			return;

		edge = graph->vexs[u]->first_edge;
		while (edge != NULL)
		{
			Relax(graph, u, edge->ivex);
			edge = edge->next_edge;
		}

	}


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
	Dijkstra(G, 1);
}