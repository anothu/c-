// GraphCPro.cpp: �������̨Ӧ�ó������ڵ㡣
#include"stdafx.h"
#include<iostream>
#include"Graph.h"
#include"Tourism.h"
using namespace std;

Graph m_Graph;


int main()
{
	while (1)
	{
		int choose;
		cout << "==========������Ϣ����ϵͳ==========" << endl;
		cout << "1.������������ͼ" << endl;
		cout << "2.��ѯ������Ϣ" << endl;
		cout << "3.���ξ��㵼��" << endl;
		cout << "4.�������·��" << endl;
		cout << "5.�����·�滮" << endl;
		cout << "0.�˳�" << endl;
		cout << "�����������ţ�0~5��:";
		cin >> choose;
		if ((choose != 1) && (choose != 2) && (choose != 3) && (choose != 4) && (choose != 5) && (choose != 0))
			cout << endl << "��������ȷ�ı��:";
		if (choose == 0)
		{
			cout << "==========���˳�==========" << endl;
			break;
		}
		else
		{
			switch (choose)
			{
			case 1:
				CreateGraph();
				break;
			case 2:
				GetSPotInfo();
				break;
			case 3:
				TravelPath();
				break;
			case 4:
				FindShortPath();
				break;
			case 5:
				DesigePath();
				break;
			}
		}
	}

	return 0;
}

