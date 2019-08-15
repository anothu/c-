
#include"stdafx.h"
#include<iostream>
#include <fstream>
#include"Tourism.h"
#include"Graph.h"
#include <string.h>
#include <vector>
#include <math.h>
#include<assert.h>
using namespace std;

extern CGraph m_Graph;

void CreatGraph()
{
	cout << "=====�������㾰��ͼ=====" << endl;
	int n;
	FILE *in;
	in = fopen("VEX.TXT", "r");
	n = fgetc(in);

	Vex *sights=new Vex[999];
	for (int i = 0; i <n-48; i++)
	{
		fscanf(in, "%d %s %s ", &sights[i].num, sights[i].name, sights[i].desc);
	}
	fclose(in);

	FILE *road;
	road = fopen("EDGE.TXT", "r");
	
	Edge *Road=new Edge[999];
	int temp = 0;
	while (1)
	{
		fscanf(road, "%d %d %d", &Road[temp].vex1, &Road[temp].vex2, &Road[temp].weight);
		temp++;
		if (feof(road))
			break;
	}
	
	for (int i = 0; i < n-48; i++)
	{
		m_Graph.InsertVex(sights[i]);
	}
	for (int i = 0; i < temp; i++) 
	{
		m_Graph.InsertEdge(Road[i]);
	}
}
void GetSpotInfo()
{
	int nVexNum = m_Graph.m_nVexNum;
	if (nVexNum == 0) {
		cout << "���ȴ���ͼ��" << endl;
		return;
	}
	cout << "��������Ҫ���ҵľ�����: ";
	int section;
	cin >> section;
	Vex s=GetVex(section);
	cout << s.num << endl << s.name << endl << s.desc<<endl;
	cout << "----�ܱ߾���-------"<<endl;
	FindEdge(section);
}

void TravelPath()
{
	//�������ǰ�����Լ����
	cout << "=====���ξ��㵼��=====" << endl;
	int nVexNum = m_Graph.m_nVexNum;
	if (nVexNum == 0) {
		cout << "���ȴ���ͼ��" << endl;
		return;
	}
	for (int i = 0; i<m_Graph.m_nVexNum; i++)
	{
		Vex sVex = GetVex(i);
		cout << i << "-" << sVex.name << endl;
	}

	//��ʾ�û�ѡ�񾰵����
	cout << "��������Ҫ��ʼ���ţ�";
	int startplace;		//�����
	cin >> startplace;
	//�ж��û������Ƿ���Ϲ淶
	if (startplace<0 || startplace >= m_Graph.m_nVexNum)
	{
		cout << "�������" << endl;
		return;
	}

	//��ѯ��startplace��ʼ��·����Ϣ
	PathList pList = new Path;
	PathList pHead = pList;
	//�õ�·����Ϣ
	DFSTraverse(startplace, pList);

	//���·����Ϣ
	cout << "���ο�·�ߣ�" << endl;
	int i = 1;
	pList = pHead;			//ͷָ��һֱ�ڣ����丳ֵ��pList��������������
	while (pList->next != NULL)
	{
		//���һ��·����Ϣ
		Vex sVex = GetVex(pList->vexs[0]);
		cout << "·��" << i++ << "��" << sVex.name;
		for (int j = 1; j<m_Graph.m_nVexNum; j++)
		{
			sVex = GetVex(pList->vexs[j]);
			cout << "->" << sVex.name;
		}
		cout << endl;
		pList = pList->next;		//ָ��������ƣ�������һ�����
	}
	cout << endl;
	//ָ��������
	delete pList;
	pList = NULL;
	pHead = NULL;
}

void ShortPath()
{
	int nVexNum = m_Graph.m_nVexNum;
	if (nVexNum == 0) {
		cout << "���ȴ���ͼ��" << endl;
		return;
	}

	cout << "=========Ѱ�����·��==========" << endl;
	for (int i = 0; i<m_Graph.m_nVexNum; i++)
	{
		Vex sVex = GetVex(i);
		cout << i << "-" << sVex.name << endl;
	}
	cout << "���������,Ŀ�ĵر��:"<<endl;
	int nVexStart, nVexEnd;
	cin >> nVexStart;
	cin >> nVexEnd;
	Edge path[999];
	FindShortPath( nVexStart,  nVexEnd,path);
	shortpath(path, nVexStart, nVexEnd);
}
void ElectricPath()
{
	int nVexNum = m_Graph.m_nVexNum;
	if (nVexNum == 0) {
		cout << "���ȴ���ͼ��" << endl;
		return;
	}
	cout << "=========�����·�滮==========" << endl;
	Edge path[999];
	int min = 99999999;
	int temp;
	for (int i = 0; i < m_Graph.m_nVexNum;i++)
	{
		if (findElectricpath(i, path) < min)
		{
			min = findElectricpath(i, path);
			temp = i;
		}
	}
	cout<<"�ܳ���:"<<findElectricpath(temp, path)<<endl;
	cout << "���跽ʽ��";
	for (int i = 2; i <= m_Graph.m_nVexNum; i++)
	{
		cout << path[i].vex1 << "->" << path[i].vex2 << " ";
	}
}
