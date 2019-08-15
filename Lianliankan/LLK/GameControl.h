#pragma once
#include"GameLogic.h"
#include"global.h"

class CGameControl
{
public:
	CGameControl();
	~CGameControl();
	void StartGame();
	int GetElement(int nRow, int nCol);
	void SetFirstPoint(int nRow, int nCol);             //���õ�һ���㺯��
	void SetSecPoint(int nRow, int nCol);   //���õڶ����㺯��
	bool Link(Vertex avPath[4], int &nVexnum);
	Vertex m_svSelFst;	//��һ��ѡ�еĵ�(x��ʾ��)
	Vertex m_svSelSec;		//�ڶ���ѡ�еĵ�
	
public:
	//int **m_PGameMap;
	static int s_nRows;
	static int s_nCols;
	static int s_nPicNum;
	int m_PGameMap[4][4];


};

