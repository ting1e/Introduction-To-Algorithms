#pragma once
#include "..//base.h"


enum Color { white,gray,black };

// 邻接表中表对应的链表的顶点
typedef struct _ENode
{
	int ivex;                   // 该边所指向的顶点的位置
	struct _ENode *next_edge;   // 指向下一条弧的指针
}ENode, *PENode;

// 邻接表中表的顶点
typedef struct _VNode
{
	char data;              // 顶点信息
	enum Color color;		//颜色
	struct _VNode *pre;		//前驱结点

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
	VNode vexs[SIZE];
}LGraph;

