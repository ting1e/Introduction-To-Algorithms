#pragma once
#include "..//base.h"

enum Color { white,gray,black };

// 邻接表中表对应的链表的顶点
typedef struct _ENode
{
	int ivex;                   // 该边所指向的顶点的位置
	int source;				//前节点
	int weight;				//权重
	struct _ENode *next_edge;   // 该边指向下一条弧的指针
}ENode, *PENode;

// 邻接表中表的顶点
typedef struct _VNode
{
	char data;              // 顶点信息
	enum Color color;		//颜色
	int pre;		//前驱结点
	int category;
	int d;					//源节点到当前节点的距离
	int f;
	//  dfs中 d 开始时间，f 结束时间。
	ENode *first_edge;      // 指向第一条依附该顶点的弧
}VNode;

// 邻接表
typedef struct _LGraph
{
	int vexnum;             // 图的顶点的数目
	int edgnum;             // 图的边的数目
	VNode *vexs[SIZE];
}LGraph;


LGraph *CreateGraph(int msg[][10], int vexs,int edges)
{
	LGraph *G = (LGraph *)malloc(sizeof(LGraph));
	G->vexnum = vexs;
	G->edgnum = edges;

	for (int i = 0; i < vexs; i++)
	{
		VNode *vnode = (VNode *)malloc(sizeof(VNode));
		vnode->data = i + 'a' ;
		vnode->first_edge = NULL;
		vnode->pre = 0;

		for (int j = 0; j <vexs; j++)
		{
			if (msg[i][j] != 0)
			{
				if (vnode->first_edge == NULL)
				{
					ENode *edge = (ENode *)malloc(sizeof(ENode));

					edge->ivex = j+1;
					edge->weight = msg[i][j];
					edge->next_edge = NULL;
					vnode->first_edge = edge;
				}
				else
				{
					ENode * pre_Lnode = vnode->first_edge;
					while (pre_Lnode->next_edge != NULL)
					{
						pre_Lnode = pre_Lnode->next_edge;
					}
					ENode *edge = (ENode *)malloc(sizeof(ENode));

					edge->ivex = j + 1;
					edge->weight = msg[i][j];
					edge->next_edge = NULL;
					pre_Lnode->next_edge = edge;
				}
			}
		}
		G->vexs[i+1] = vnode;
	}
	return G;
}



void DestroyGraph(LGraph *G)
{
	for (int i = 1; i <= G->vexnum; i++)
	{
		if (G->vexs[i]->first_edge == NULL)
		{
			free(G->vexs[i]);
		}
		else
		{
			ENode *temp = G->vexs[i]->first_edge;
			while (temp!=NULL)
			{
				ENode *del_node = temp;
				temp = temp->next_edge;
				free(del_node);	
			}
		}
		free(G->vexs[i]);
	}
	free(G);
}

LGraph *TransposeGraph(LGraph *G)
{
	LGraph *new_graph = (LGraph *)malloc(sizeof(LGraph));
	new_graph->vexnum = G->vexnum;
	new_graph->edgnum = G->edgnum;
	for (int i = 1; i <= G->vexnum; i++)
	{
		new_graph->vexs[i] = (VNode *)malloc(sizeof(VNode));
		new_graph->vexs[i]->color = G->vexs[i]->color;
		new_graph->vexs[i]->d = G->vexs[i]->d;
		new_graph->vexs[i]->f = G->vexs[i]->f;
		new_graph->vexs[i]->data = G->vexs[i]->data;
		new_graph->vexs[i]->first_edge = NULL;

	}
	for (int i = 1; i <= G->vexnum; i++)
	{

		ENode *edge = G->vexs[i]->first_edge;
		while (edge != NULL)
		{
			if (new_graph->vexs[edge->ivex]->first_edge == NULL)
			{
				new_graph->vexs[edge->ivex]->first_edge = (ENode *)malloc(sizeof(ENode));
				new_graph->vexs[edge->ivex]->first_edge->ivex = i;
				new_graph->vexs[edge->ivex]->first_edge->next_edge = NULL;
			}
			else
			{
				ENode *par_edge = new_graph->vexs[edge->ivex]->first_edge;
				while (par_edge->next_edge != NULL)
					par_edge = par_edge->next_edge;
				par_edge->next_edge= (ENode *)malloc(sizeof(ENode));
				par_edge->next_edge->ivex = i;
				par_edge->next_edge->next_edge = NULL;

			}
			edge = edge->next_edge;
		}

	}
	return new_graph;
}
