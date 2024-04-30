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
		cout << "Vertexes.txt�ļ���ʧ�ܣ�" << endl;
		return;
	}

	// �ݴ��Vex.txt��ȡ����һ������
	char num[2];
	char name[32];
	char desc[1024];
	Vex sVex;

	// ���ж�ȡVex.txt�е�����
	VexFile.getline(num, 2);
	
	cout << "������Ŀ��" << atoi(num) << endl;
	cout << "=========����=========" << endl;

	// ��������Ϣ���浽����������
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
			cout << "��������ʧ�ܣ�" << endl;
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
		cout << "Edges.txt�ļ���ʧ�ܣ�" << endl;
		return;
	}

	Edge edge;
	cout << "=========·��=========" << endl;
	while (EdgeFile)
	{
		EdgeFile >> edge.vex1 >> edge.vex2 >> edge.weight;
		cout << "<" << edge.vex1 << "��" << edge.vex2 << ">  " << edge.weight << "km" << endl;

		// ����ͼ�ı�
		if (!InsertEdge(edge))
		{
			cout << "����·��ʧ�ܣ�" << endl;
			continue;
		}
	}
	cout << "======================" << endl;
	EdgeFile.close();
}


void CreateGraph()
{
	cout << "\n======��������ͼ======" << endl;
	Init();
	LoadVex();
	LoadPath();
	cout << endl;
}


void GetSpotInfo()
{
	cout << "\n====��ѯ������Ϣ====" << endl;
	int nVexNum = MGraph.VexNum;
	if (nVexNum == 0)
	{
		cout << "���ȴ�������ͼ��" << endl;
		return;
	}

	// ��������Ϣ�г��������û���ѯѡ��
	for (int i = 0; i < MGraph.VexNum; i++)
	{
		Vex sVex = GetVex(i);
		cout << i << " - " << sVex.name << endl;
	}

	cout << "====================" << endl;
	cout << "��������Ҫ��ѯ�ľ���ı�ţ�";
	int num;
	cin >> num;
	while (num < 0 || num >= MGraph.VexNum)
	{
		cout << "����������������ȷ�ľ����ţ�" << endl;
		cin >> num;
	}
	Vex sVex = GetVex(num);
	cout << "\n====================" << endl;
	cout << sVex.name << "��" << sVex.desc << endl;
	cout << "====================" << endl;
	cout << "\n======�ܱ߾���======" << endl;
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
	cout << "\n=====����·�߹滮=====" << endl;
	int nVexNum = MGraph.VexNum;
	if (nVexNum == 0)
	{
		cout << "���ȴ�������ͼ��" << endl;
		return;
	}
	for (int i = 0; i < MGraph.VexNum; i++)
	{
		Vex sVex = GetVex(i);
		cout << i << " - " << sVex.name << "\t\t" << endl;
	}
	cout << "======================" << endl;

	// ���뾰����
	cout << "����������ţ�";
	int start;
	cin >> start;
	while (start < 0 || start >= MGraph.VexNum)
	{
		cout << "����������������ȷ������ţ�" << endl;
		cin >> start;
	}
	
	// ��������ͼ
	PathList pList = new Path;
	PathList pHead = pList;
	DFSTraverse(start, pList);
	cout << endl;

	// ����������
	cout << "�ɹ�ѡ�������·��Ϊ��" << endl;
	int i = 1;
	pList = pHead;
	while (pList->next != NULL)
	{
		Vex vex = GetVex(pList->vexs[0]);
		cout << "·��" << i++ << "��" << vex.name;
		for (int j = 1; j < MGraph.VexNum; j++)
		{
			vex = GetVex(pList->vexs[j]);
			cout << "��>" << vex.name;
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
	cout << "\n=====���·�ߵ���=====" << endl;
	int nVexNum = MGraph.VexNum;
	if (nVexNum == 0)
	{
		cout << "���ȴ���ͼ��" << endl;
		return;
	}
	for (int i = 0; i < MGraph.VexNum; i++)
	{
		Vex sVex = GetVex(i);
		cout << i << "-" << sVex.name << "\t\t" << endl;
	}
	cout << "======================" << endl;

	int splace, eplace;
	cout << "����������ţ�";
	cin >> splace;
	cout << "�������յ��ţ�";
	cin >> eplace;

	if (splace < 0 || splace >= MGraph.VexNum || eplace < 0 || eplace >= MGraph.VexNum)
	{
		cout << "����������������ȷ����ֹ���ţ�" << endl;
		cout << "����������ţ�";
		cin >> splace;
		cout << "�������յ��ţ�";
		cin >> eplace;
	}

	Edge Path[20];
	for (int i = 0; i < 20; i++)
	{
		Path->vex1 = -1;
		Path->vex2 = -1;
		Path->weight = -1;
	}

	// �������·������̾���
	int index = FindShortestPath(splace, eplace, Path);
	int length = 0;
	Vex sVex = GetVex(Path[0].vex1);
	cout << "\n���·��Ϊ��" << sVex.name;
	for (int i = 0; i < index; i++)
	{
		sVex = GetVex(Path[i].vex2);
		cout << "��>" << sVex.name;
		length += Path[i].weight;
	}

	cout << endl;
	cout << "��̾���Ϊ��" << length << "km" << endl
		 << endl;
}


void DesignPath()
{
	cout << "\n�����¾���֮�佨�����" << endl;
	cout << "======================" << endl;
	Edge Path[20];

	// ��Prim������С������
	Prim(Path);

	int nVexNum = MGraph.VexNum;
	if (nVexNum == 0)
	{
		cout << "���ȴ�������ͼ��" << endl;
		return;
	}

	// ���������·ͼ
	int AllLength = 0;
	for (int i = 0; i < MGraph.VexNum - 1; i++)
	{
		Vex nVex1 = GetVex(Path[i].vex1);
		Vex nVex2 = GetVex(Path[i].vex2);
		cout << nVex1.name << " �� " << nVex2.name << "��" << Path[i].weight << "km" << endl;
		AllLength += Path[i].weight;
	}
	cout << "�����·�ܳ��ȣ�" << AllLength << "km" << endl;
	cout << "======================" << endl
		 << endl;
}