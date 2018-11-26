#pragma once

#include "23_2_KruskalÀ„∑®.h"


ENode *FindMinSafeEdge(LGraph *G, LGraph *new_G)
{
	ENode *min_edge = NULL;
	int weight = 100;

	for (int i = 1; i <= G->vexnum; i++)
	{
		if (new_G->vexs[i]->category == new_G->vexs[1]->category)
		{
			ENode *temp = G->vexs[i]->first_edge;
			while (temp!=NULL)
			{
				if (temp->weight < weight&&new_G->vexs[temp->ivex]->category != new_G->vexs[1]->category)
				{
					min_edge = temp;
					weight = temp->weight;
				}
				temp = temp->next_edge;
			}
		}
	}
	return min_edge;
}

int IsFinished(LGraph *new_G)
{
	for (int i = 1; i <= new_G->vexnum; i++)
	{
		if (new_G->vexs[i]->category != new_G->vexs[1]->category)
		{
			return 0;
		}
	}
	return 1;
}


LGraph *MSTPrim(LGraph *G)
{
	LGraph *new_G = MakeSet(G);
	ENode *edge = NULL;
	VNode *vnode = NULL;
	while (!IsFinished(new_G))
	{
		edge = FindMinSafeEdge(G, new_G);

		vnode = new_G->vexs[edge->source];
		if (vnode->first_edge == NULL)
		{
			ENode *new_edge = (ENode *)malloc(sizeof(ENode));

			new_edge->ivex = edge->ivex;
			new_edge->weight = edge->weight;
			new_edge->source = edge->source;
			new_edge->next_edge = NULL;
			vnode->first_edge = new_edge;
		}
		else
		{
			ENode * pre_Lnode = vnode->first_edge;
			while (pre_Lnode->next_edge != NULL)
			{
				pre_Lnode = pre_Lnode->next_edge;
			}
			ENode *new_edge = (ENode *)malloc(sizeof(ENode));

			new_edge->ivex = edge->ivex;
			new_edge->weight = edge->weight;
			new_edge->source = edge->source;
			new_edge->next_edge = NULL;
			pre_Lnode->next_edge = new_edge;
		}

		vnode = new_G->vexs[edge->ivex];

		vnode->category = new_G->vexs[1]->category;
		if (vnode->first_edge == NULL)
		{
			ENode *new_edge = (ENode *)malloc(sizeof(ENode));

			new_edge->ivex = edge->source;
			new_edge->weight = edge->weight;
			new_edge->source = edge->source;
			new_edge->next_edge = NULL;
			vnode->first_edge = new_edge;
		}
		else
		{
			ENode * pre_Lnode = vnode->first_edge;
			while (pre_Lnode->next_edge != NULL)
			{
				pre_Lnode = pre_Lnode->next_edge;
			}
			ENode *new_edge = (ENode *)malloc(sizeof(ENode));

			new_edge->ivex = edge->source;
			new_edge->weight = edge->weight;
			new_edge->source = edge->ivex;
			new_edge->next_edge = NULL;
			pre_Lnode->next_edge = new_edge;
		}

	}
	return new_G;
}




void test1()
{
	int msg[9][10] =
	{
		2,8,0,0,0,0,0,0,0,0,
		1,3,8,0,0,0,0,0,0,0,
		2,4,6,9,0,0,0,0,0,0,
		3,5,6,0,0,0,0,0,0,0,
		4,6,0,0,0,0,0,0,0,0,

		3,4,5,7,0,0,0,0,0,0,
		6,8,9,0,0,0,0,0,0,0,
		1,2,7,9,0,0,0,0,0,0,
		3,7,8,0,0,0,0,0,0,0,
	};
	int weight[9][10] =
	{
		4,8,0,0,0,0,0,0,0,0,
		4,8,11,0,0,0,0,0,0,0,
		8,7,4,2,0,0,0,0,0,0,
		7,9,14,0,0,0,0,0,0,0,
		9,10,0,0,0,0,0,0,0,0,

		4,14,10,2,0,0,0,0,0,0,
		2,1,6,0,0,0,0,0,0,0,
		8,11,1,7,0,0,0,0,0,0,
		2,6,7,0,0,0,0,0,0,0,
	};

	LGraph *G = CreateGraphWithWidth(msg, weight, 9, 28);
	LGraph *mst_G = MSTPrim(G);
	printf("");
	DestroyGraph(G);
	DestroyGraph(mst_G);
}