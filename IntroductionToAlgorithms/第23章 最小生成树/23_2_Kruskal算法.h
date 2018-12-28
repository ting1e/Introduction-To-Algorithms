#pragma once

#include "../第22章 基本的图算法/22_1_图的表示.h"



LGraph *MakeSet(LGraph* G)
{
	LGraph *new_G = (LGraph *)malloc(sizeof(LGraph));
	new_G->vexnum = G->vexnum;
	for (int i = 1; i <= G->vexnum; i++)
	{
		VNode *vnode = (VNode *)malloc(sizeof(VNode));
		vnode->category = i;
		vnode->data = G->vexs[i]->data;
		vnode->first_edge = NULL;
		new_G->vexs[i] = vnode;
	}
	return new_G;
}

void SortByWeight(ENode * arr[], int length)
{
	for (int i = 1; i < length; i++)
	{
		for (int j = i; j > 0 && (arr[j]->weight < arr[j - 1]->weight); j--)
		{
			ENode *temp = arr[j-1];
			arr[j-1] = arr[j];
			arr[j] = temp;

		}
	}

	for (int i = 0; i < length; i++)
	{
		int another = i + 1;
		while (!((arr[i]->source==arr[another]->ivex)&&(arr[another]->source == arr[i]->ivex)))
		{
			another++;
		}

		ENode *temp = arr[i+1];
		arr[i+1] = arr[another];
		arr[another] = temp;
		i++;
	}

}

ENode **SortEdges(LGraph *G)
{
	ENode **sorted_edges = (ENode**)malloc(sizeof(ENode *)* G->edgnum);
	int num = 0;

	for (int i = 1; i <= G->vexnum; i++)
	{
		ENode *temp = G->vexs[i]->first_edge;
		while (temp != NULL)
		{
			
			ENode *new_edge = (ENode *)malloc(sizeof(ENode));

			new_edge->ivex = temp->ivex;
			new_edge->weight = temp->weight;
			new_edge->next_edge = NULL;
			new_edge->source = temp->source;

			sorted_edges[num++] = new_edge;

			temp = temp->next_edge;

		}
	}
	
	SortByWeight(sorted_edges, num);
	return sorted_edges;
}

LGraph *MSTKruskal(LGraph *G)
{
	LGraph *set = MakeSet(G);
	ENode **sorted_edges = SortEdges(G);
	for (int i = 0; i < G->edgnum; i++)
	{
		if (set->vexs[sorted_edges[i]->source]->category!= set->vexs[sorted_edges[i]->ivex]->category)
		{
			int cat = set->vexs[sorted_edges[i]->ivex]->category;
			for (int i = 1; i <= G->vexnum; i++)
			{
				if (set->vexs[i]->category == cat)
				{
					set->vexs[i]->category = set->vexs[sorted_edges[i]->source]->category;
				}
			}

			VNode *vnode = set->vexs[sorted_edges[i]->source];
			if (vnode->first_edge == NULL)
			{
				vnode->first_edge = sorted_edges[i];
			}
			else
			{
				ENode * pre_Lnode = vnode->first_edge;
				while (pre_Lnode->next_edge != NULL)
				{
					pre_Lnode = pre_Lnode->next_edge;
				}
				
				pre_Lnode->next_edge = sorted_edges[i];
			}

			vnode = set->vexs[sorted_edges[i]->ivex];
			if (vnode->first_edge == NULL)
			{
				vnode->first_edge = sorted_edges[++i];
			}
			else
			{
				ENode * pre_Lnode = vnode->first_edge;
				while (pre_Lnode->next_edge != NULL)
				{
					pre_Lnode = pre_Lnode->next_edge;
				}

				pre_Lnode->next_edge = sorted_edges[++i];
			}

		}
	}
	return set;

}

void test()
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

	LGraph *G = CreateGraphWithWidth(msg,weight, 9, 28);
	LGraph *mst_G = MSTKruskal(G);
	printf("");
	DestroyGraph(G);
	DestroyGraph(mst_G);
}