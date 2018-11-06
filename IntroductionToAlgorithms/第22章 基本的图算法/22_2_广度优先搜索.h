#pragma once
#include "22_1_图的表示.h"

#define TYPE VNode*

#include "../第10章 基本数据结构/10_1_栈和队列.h"



void PrintPath(LGraph *G, VNode *s, VNode *v)
{
	if (v == s)
		printf("%c", s->data);
	else if (v->pre == NULL)
		printf("no path from s to v exists");
	else
	{
		PrintPath(G, s, v->pre);
		printf("%c", v->data);
	}
}

//广度优先遍历  雨露均沾
void BFS(LGraph* G, VNode* s)
{
	VNode* u;
	int i;	
	for (i = 0; i < G->vexnum; i++)
	{
		G->vexs[i].color = white;
		G->vexs[i].d = INT_MAX;
		G->vexs[i].pre = NULL;
	}
	s->color = gray;
	s->pre = NULL;
	s->d = 0;
	printf("%c ",s->data);
	struct Queue queue;
	InitQueue(&queue);
	EnQueue(&queue, s);
	while (queue.head != queue.tail)  //队列非空
	{
		DeQueue(&queue, &u);
		ENode *edge = u->first_edge;
		while (edge!=NULL)
		{
			if (G->vexs[edge->ivex].color == white)
			{
				printf("%c ", G->vexs[edge->ivex].data);
				G->vexs[edge->ivex].color = gray;
				G->vexs[edge->ivex].d = u->d + 1;
				G->vexs[edge->ivex].pre = u;
				EnQueue(&queue, &G->vexs[edge->ivex]);
			}
			edge = edge->next_edge;
		}
		u->color = black;
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

	LGraph G;
	G.edgnum = 10;
	G.vexnum = 8;

	VNode node_r;
	node_r.data = 'r';
	ENode r_edge1;
	ENode r_edge2;

	r_edge1.ivex = 2;
	r_edge1.next_edge = &r_edge2;
	r_edge2.ivex = 1;
	r_edge2.next_edge = NULL;
	node_r.first_edge = &r_edge1;

	G.vexs[0] = node_r;


	VNode node_v;
	node_v.data = 'v';
	ENode v_edge1;

	v_edge1.ivex = 0;
	v_edge1.next_edge = NULL;

	node_v.first_edge = &v_edge1;

	G.vexs[1] = node_v;


	VNode node_s;
	node_s.data = 's';
	ENode s_edge1;
	ENode s_edge2;

	s_edge1.ivex = 0;
	s_edge1.next_edge = &s_edge2;
	s_edge2.ivex = 3;
	s_edge2.next_edge = NULL;
	node_s.first_edge = &s_edge1;

	G.vexs[2] = node_s;


	VNode node_w;
	node_w.data = 'w';
	ENode w_edge1;
	ENode w_edge2;
	ENode w_edge3;

	w_edge1.ivex = 2;
	w_edge1.next_edge = &w_edge2;
	w_edge2.ivex = 4;
	w_edge2.next_edge = &w_edge3;
	w_edge3.ivex = 5;
	w_edge3.next_edge = NULL;

	node_w.first_edge = &w_edge1;

	G.vexs[3] = node_w;


	VNode node_t;
	node_t.data = 't';
	ENode t_edge1;
	ENode t_edge2;
	ENode t_edge3;

	t_edge1.ivex = 3;
	t_edge1.next_edge = &t_edge2;
	t_edge2.ivex = 5;
	t_edge2.next_edge = &t_edge3;
	t_edge3.ivex = 6;
	t_edge3.next_edge = NULL;

	node_t.first_edge = &t_edge1;

	G.vexs[4] = node_t;


	VNode node_x;
	node_x.data = 'x';
	ENode x_edge1;
	ENode x_edge2;
	ENode x_edge3;
	ENode x_edge4;

	x_edge1.ivex = 3;
	x_edge1.next_edge = &x_edge2;
	x_edge2.ivex = 4;
	x_edge2.next_edge = &x_edge3;
	x_edge3.ivex = 6;
	x_edge3.next_edge = &x_edge4;
	x_edge4.ivex = 7;
	x_edge4.next_edge = NULL;
	node_x.first_edge = &x_edge1;

	G.vexs[5] = node_x;


	VNode node_u;
	node_u.data = 'u';
	ENode u_edge1;
	ENode u_edge2;
	ENode u_edge3;

	u_edge1.ivex = 4;
	u_edge1.next_edge = &u_edge2;
	u_edge2.ivex = 5;
	u_edge2.next_edge = &u_edge3;
	u_edge3.ivex = 7;
	u_edge3.next_edge = NULL;

	node_u.first_edge = &u_edge1;

	G.vexs[6] = node_u;


	VNode node_y;
	node_y.data = 'y';
	ENode y_edge1;
	ENode y_edge2;

	y_edge1.ivex = 5;
	y_edge1.next_edge = &y_edge2;
	y_edge2.ivex = 6;
	y_edge2.next_edge = NULL;

	node_y.first_edge = &y_edge1;

	G.vexs[7] = node_y;


	BFS(&G, &G.vexs[2]);
	PrintPath(&G, &G.vexs[2], &G.vexs[6]);
}
