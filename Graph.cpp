#pragma warning(disable:4996)
#include <iostream>
#include <stdlib.h>
#include "Tourism.h"

using namespace std;

extern Graph MGraph;

void Init()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
			MGraph.AdjMatrix[i][j] = 0;
		MGraph.VexNum = 0;
	}
}


bool InsertVex(Vex sVex)
{
	if (MGraph.VexNum == 20)
		return false;
	MGraph.vexs[MGraph.VexNum++] = sVex;
	return true;
}


bool InsertEdge(Edge sEdge)
{
	if (sEdge.vex1 < 0 || sEdge.vex1 >= MGraph.VexNum || sEdge.vex2 < 0 || sEdge.vex2 >= MGraph.VexNum)
		return false;
	MGraph.AdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	MGraph.AdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;
	return true;
}


Vex GetVex(int Vex)
{
	return MGraph.vexs[Vex];
}


int FindEdge(int Vex, Edge Edge[])
{
	int k = 0;
	for (int i = 0; i < 20; i++)
	{
		if (MGraph.AdjMatrix[Vex][i] != 0 && Vex != i)
		{
			Edge[k].vex1 = Vex;
			Edge[k].vex2 = i;
			Edge[k].weight = MGraph.AdjMatrix[Vex][i];
			k++;
		}
	}
	return k;
}


void DFS(int Vex, bool visited[], int &Index, PathList &pList)
{
	visited[Vex] = true;
	pList->vexs[Index++] = Vex;
	
	int num = 0;  // 已被访问的节点数
	for (int i = 0; i < MGraph.VexNum; i++)
	{
		if (visited[i])
			num++;
	}

	if (num == MGraph.VexNum)
	{
	// 如果所有节点都被访问过，则将当前路径加入路径链表
		pList->next = new Path;
		for (int i = 0; i < MGraph.VexNum; i++)
			pList->next->vexs[i] = pList->vexs[i];
		pList = pList->next;
		pList->next = NULL;
	}
	else {
		for (int w = 0; w < MGraph.VexNum; w++)
		{
			// 遍历Vex的每个邻接点
			if (MGraph.AdjMatrix[Vex][w] > 0 && !visited[w])
			{
				DFS(w, visited, Index, pList);
				visited[w] = false;
				Index--;
			}
		}
	}
}


void DFSTraverse(int Vex, PathList& pList)
{
	bool visited[20] = { false };
	int Index = 0;
	DFS(Vex, visited, Index, pList);
}


int FindShortestPath(int SVex, int EVex, Edge Path[])
{
	int SPath[20][20];
	int SDist[20];
	bool visited[20];
	int v;  // 每次找到的可加入集合的顶点

	// 初始化
	for (v = 0; v < MGraph.VexNum; v++)
	{
		visited[v] = false;
		// 初始顶点与各邻接点的距离
		if (MGraph.AdjMatrix[SVex][v] != 0)
			SDist[v] = MGraph.AdjMatrix[SVex][v];
		else
			SDist[v] = 0x7FFFFFFF;
		SPath[v][0] = SVex;
		for(int i = 1; i < MGraph.VexNum; i++)
			SPath[v][i] = -1;
	}
	visited[SVex] = true;

	int min;  // 记录当前最小距离
	for (int i = 1; i < MGraph.VexNum; i++)
	{
		min = 0x7FFFFFFF;
		bool Add = false;
		for (int w = 0; w < MGraph.VexNum; w++)
		{
			if (!visited[w] && SDist[w] < min)
			{
				v = w;
				min = SDist[w];
				Add = true;
			}
		}
		// 如果没有顶点加入，则表示已查找完毕
		if (!Add)
			break;

		visited[v] = true;
		SPath[v][i] = v;

		for (int w = 0; w < MGraph.VexNum; w++)
		{
			if (!visited[w] && MGraph.AdjMatrix[v][w] > 0 && (min + MGraph.AdjMatrix[v][w] < SDist[w]))
			{
				// 如果有新的最短路径，则更新路径和距离
				SDist[w] = min + MGraph.AdjMatrix[v][w];
				for (int j = 0; j < MGraph.VexNum; j++)
					SPath[w][j] = SPath[v][j];
			}
		}
	}

	int Index = 0;
	int vex1 = SVex;

	// 将最短路径保存到边的结构体数组中
	for (int i = 1; i < MGraph.VexNum; i++)
	{
		if (SPath[EVex][i] != -1) {
			Path[Index].vex1 = vex1;
			Path[Index].vex2 = SPath[EVex][i];
			Path[Index].weight = MGraph.AdjMatrix[vex1][Path[Index].vex2];
			vex1 = SPath[EVex][i];
			Index++;
		}
	}
	return Index;
}


void Prim(Edge MST[])
{
	bool visited[20] = { false };
	visited[0] = true;
	int min, vex1, vex2;

	for (int i = 0; i < MGraph.VexNum - 1; i++)
	{
		min = 0x7FFFFFFF;
		for (int j = 0; j < MGraph.VexNum; j++)
		{
			// 从集合中取出一个顶点
			if (visited[j])
			{
				// 从不在集合的定点中取一个顶点
				for (int k = 0; k < MGraph.VexNum; k++)
				{
					if (!visited[k])
					{
						if ((MGraph.AdjMatrix[j][k] < min) && (MGraph.AdjMatrix[j][k] != 0))
						{
							// 找到新的最小边，更新顶点和最小边
							vex1 = j;
							vex2 = k;
							min = MGraph.AdjMatrix[j][k];
						}
					}
				}
			}
		}
		// 保存最短边的两个顶点并将其加入集合
		MST[i].vex1 = vex1;
		MST[i].vex2 = vex2;
		MST[i].weight = MGraph.AdjMatrix[vex1][vex2];;
		visited[vex1] = true;
		visited[vex2] = true;
	}
}