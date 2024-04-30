#pragma once

// 图的顶点信息
typedef struct Vex {
	int num;  // 景点编号
	char name[32];  // 景点名称
	char desc[1024];  // 介绍信息
}Vex;

// 图的边信息
typedef struct Edge{
	int vex1, vex2;  // 边的两端点
	int weight;  // 边的长度
}Edge;

// 景区景点图
typedef struct Graph {
	int AdjMatrix[20][20];  // 邻接矩阵
	Vex vexs[20];  // 顶点数组
	int VexNum;  // 顶点个数
}Graph;

// 定义链表PathList
typedef struct Path {
	int vexs[20];  // 顶点编号
	Path* next;  // 指向下一个顶点的指针
}* PathList;


// 初始化图结构
void Init();

// 将顶点添加到顶点数组
bool InsertVex(Vex sVex);

// 将边保存到邻接矩阵中
bool InsertEdge(Edge sEdge);

// 查询指定顶点信息
Vex GetVex(int Vex);

// 查询与指定顶点相连的边
int FindEdge(int Vex, Edge sEdge[]);

// 深度优先搜索算法遍历图
void DFS(int Vex, bool visited[], int& Index, PathList& pList);

// 通过深度优先搜索获得遍历结果
void DFSTraverse(int Vex, PathList& pList);

// 寻找最短路径
int FindShortestPath(int SVex, int EVex, Edge Path[]);

// 用Prim算法生成最小生成树
void Prim(Edge MST[]);