#pragma once

// ͼ�Ķ�����Ϣ
typedef struct Vex {
	int num;  // ������
	char name[32];  // ��������
	char desc[1024];  // ������Ϣ
}Vex;

// ͼ�ı���Ϣ
typedef struct Edge{
	int vex1, vex2;  // �ߵ����˵�
	int weight;  // �ߵĳ���
}Edge;

// ��������ͼ
typedef struct Graph {
	int AdjMatrix[20][20];  // �ڽӾ���
	Vex vexs[20];  // ��������
	int VexNum;  // �������
}Graph;

// ��������PathList
typedef struct Path {
	int vexs[20];  // ������
	Path* next;  // ָ����һ�������ָ��
}* PathList;


// ��ʼ��ͼ�ṹ
void Init();

// ��������ӵ���������
bool InsertVex(Vex sVex);

// ���߱��浽�ڽӾ�����
bool InsertEdge(Edge sEdge);

// ��ѯָ��������Ϣ
Vex GetVex(int Vex);

// ��ѯ��ָ�����������ı�
int FindEdge(int Vex, Edge sEdge[]);

// ������������㷨����ͼ
void DFS(int Vex, bool visited[], int& Index, PathList& pList);

// ͨ���������������ñ������
void DFSTraverse(int Vex, PathList& pList);

// Ѱ�����·��
int FindShortestPath(int SVex, int EVex, Edge Path[]);

// ��Prim�㷨������С������
void Prim(Edge MST[]);