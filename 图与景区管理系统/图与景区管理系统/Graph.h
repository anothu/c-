#pragma once

struct Vex
{
	int num;//���
	char name[20];//����
	char desc[1024];//����
};

struct Edge
{
	int vex1;//��һ������
	int vex2;//�ڶ�������
	int weight;//Ȩֵ
};

class CGraph
{
public:
	bool InsertVex(Vex sVex);
	bool InsertEdge(Edge sEdge);
	int m_aAdjMatrix[20][20];//�ڽӾ���
	Vex m_aVexs[20];//������Ϣ����
	int m_nVexNum;//��ǰͼ�Ķ������
};

void Init();
Vex GetVex(int v);
int FindEdge(int a);

typedef struct Path
{
	int vexs[20];
	Path *next;
}*PathList;

void DFS(int v, bool bVisited[], int &index, PathList &plist);
void DFSTraverse(int nVex, PathList & pList);
int FindShortPath(int nVexStart, int nVexEnd,Edge* path);
void shortpath(Edge path[], int nVexStart, int nVexEnd);
int findpathweight(Edge*path, int j, int n);
int i_s(int*a, int i, int num);
int findElectricpath(int nVexStart, Edge*path);
//void Minelectric();