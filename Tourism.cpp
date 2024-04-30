#pragma warning(disable:4996)
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include "Tourism.h"

using namespace std;

extern Graph MGraph;

void LoadVex()
{
	ifstream VexFile("Vertexes.txt");
	if (!VexFile)
	{
		cout << "Vertexes.txt文件打开失败！" << endl;
		return;
	}

	// 暂存从Vex.txt读取到的一行数据
	char num[2];
	char name[32];
	char desc[1024];
	Vex sVex;

	// 逐行读取Vex.txt中的数据
	VexFile.getline(num, 2);
	
	cout << "景点数目：" << atoi(num) << endl;
	cout << "=========景点=========" << endl;

	// 将定点信息保存到顶点数组中
	while (VexFile.getline(num, 2))
	{
		sVex.num = atoi(num);
		VexFile.getline(name, 32);
		strcpy(sVex.name, name);
		VexFile.getline(desc, 1024);
		strcpy(sVex.desc, desc);
		cout << sVex.num << " - " << sVex.name << endl;
		if (!InsertVex(sVex))
		{
			cout << "新增景点失败！" << endl;
			continue;
		}
	}
	cout << "======================" << endl;
	VexFile.close();
}


void LoadPath()
{
	ifstream EdgeFile("Edges.txt");
	if (!EdgeFile)
	{
		cout << "Edges.txt文件打开失败！" << endl;
		return;
	}

	Edge edge;
	cout << "=========路径=========" << endl;
	while (EdgeFile)
	{
		EdgeFile >> edge.vex1 >> edge.vex2 >> edge.weight;
		cout << "<" << edge.vex1 << "，" << edge.vex2 << ">  " << edge.weight << "km" << endl;

		// 设置图的边
		if (!InsertEdge(edge))
		{
			cout << "新增路径失败！" << endl;
			continue;
		}
	}
	cout << "======================" << endl;
	EdgeFile.close();
}


void CreateGraph()
{
	cout << "\n======创建景点图======" << endl;
	Init();
	LoadVex();
	LoadPath();
	cout << endl;
}


void GetSpotInfo()
{
	cout << "\n====查询景点信息====" << endl;
	int nVexNum = MGraph.VexNum;
	if (nVexNum == 0)
	{
		cout << "请先创建景点图！" << endl;
		return;
	}

	// 将景点信息列出来，供用户查询选择
	for (int i = 0; i < MGraph.VexNum; i++)
	{
		Vex sVex = GetVex(i);
		cout << i << " - " << sVex.name << endl;
	}

	cout << "====================" << endl;
	cout << "请输入想要查询的景点的编号：";
	int num;
	cin >> num;
	while (num < 0 || num >= MGraph.VexNum)
	{
		cout << "输入有误，请输入正确的景点编号：" << endl;
		cin >> num;
	}
	Vex sVex = GetVex(num);
	cout << "\n====================" << endl;
	cout << sVex.name << "：" << sVex.desc << endl;
	cout << "====================" << endl;
	cout << "\n======周边景区======" << endl;
	Edge aEdge[20];
	int EdgeNum = FindEdge(num, aEdge);
	for (int i = 0; i < EdgeNum; i++)
	{
		Vex v = GetVex(aEdge[i].vex2);
		cout << v.name << "  " << aEdge[i].weight << "km" << endl;
	}
	cout << "====================\n" << endl;
}


void TravelPath()
{
	cout << "\n=====旅游路线规划=====" << endl;
	int nVexNum = MGraph.VexNum;
	if (nVexNum == 0)
	{
		cout << "请先创建景点图！" << endl;
		return;
	}
	for (int i = 0; i < MGraph.VexNum; i++)
	{
		Vex sVex = GetVex(i);
		cout << i << " - " << sVex.name << "\t\t" << endl;
	}
	cout << "======================" << endl;

	// 输入景点编号
	cout << "请输入起点编号：";
	int start;
	cin >> start;
	while (start < 0 || start >= MGraph.VexNum)
	{
		cout << "输入有误，请输入正确的起点编号：" << endl;
		cin >> start;
	}
	
	// 遍历景点图
	PathList pList = new Path;
	PathList pHead = pList;
	DFSTraverse(start, pList);
	cout << endl;

	// 输出遍历结果
	cout << "可供选择的旅游路线为：" << endl;
	int i = 1;
	pList = pHead;
	while (pList->next != NULL)
	{
		Vex vex = GetVex(pList->vexs[0]);
		cout << "路线" << i++ << "：" << vex.name;
		for (int j = 1; j < MGraph.VexNum; j++)
		{
			vex = GetVex(pList->vexs[j]);
			cout << "—>" << vex.name;
		}
		cout << endl;
		pList = pList->next;
	}
	cout << endl;

	delete pList;
	pList = NULL;
	pHead = NULL;
}


void FindShortPath()
{
	cout << "\n=====最短路线导航=====" << endl;
	int nVexNum = MGraph.VexNum;
	if (nVexNum == 0)
	{
		cout << "请先创建图！" << endl;
		return;
	}
	for (int i = 0; i < MGraph.VexNum; i++)
	{
		Vex sVex = GetVex(i);
		cout << i << "-" << sVex.name << "\t\t" << endl;
	}
	cout << "======================" << endl;

	int splace, eplace;
	cout << "请输入起点编号：";
	cin >> splace;
	cout << "请输入终点编号：";
	cin >> eplace;

	if (splace < 0 || splace >= MGraph.VexNum || eplace < 0 || eplace >= MGraph.VexNum)
	{
		cout << "输入有误，请输入正确的起止点编号！" << endl;
		cout << "请输入起点编号：";
		cin >> splace;
		cout << "请输入终点编号：";
		cin >> eplace;
	}

	Edge Path[20];
	for (int i = 0; i < 20; i++)
	{
		Path->vex1 = -1;
		Path->vex2 = -1;
		Path->weight = -1;
	}

	// 查找最短路径和最短距离
	int index = FindShortestPath(splace, eplace, Path);
	int length = 0;
	Vex sVex = GetVex(Path[0].vex1);
	cout << "\n最短路线为：" << sVex.name;
	for (int i = 0; i < index; i++)
	{
		sVex = GetVex(Path[i].vex2);
		cout << "—>" << sVex.name;
		length += Path[i].weight;
	}

	cout << endl;
	cout << "最短距离为：" << length << "km" << endl
		 << endl;
}


void DesignPath()
{
	cout << "\n在以下景点之间建设轻轨" << endl;
	cout << "======================" << endl;
	Edge Path[20];

	// 用Prim创建最小生成树
	Prim(Path);

	int nVexNum = MGraph.VexNum;
	if (nVexNum == 0)
	{
		cout << "请先创建景点图！" << endl;
		return;
	}

	// 输出铺设线路图
	int AllLength = 0;
	for (int i = 0; i < MGraph.VexNum - 1; i++)
	{
		Vex nVex1 = GetVex(Path[i].vex1);
		Vex nVex2 = GetVex(Path[i].vex2);
		cout << nVex1.name << " — " << nVex2.name << "：" << Path[i].weight << "km" << endl;
		AllLength += Path[i].weight;
	}
	cout << "轻轨线路总长度：" << AllLength << "km" << endl;
	cout << "======================" << endl
		 << endl;
}