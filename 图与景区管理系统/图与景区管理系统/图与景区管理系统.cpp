// ͼ�뾰������ϵͳ.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iomanip>
#include<iostream>
#include"Graph.h"
#include"Tourism.h"
using namespace std;

CGraph m_Graph;

void information()
{	
	cout <<"������ "<< m_Graph.m_nVexNum<<endl;

	//juzheng
	for (int i = 0; i < m_Graph.m_nVexNum; i++)
	{
		for (int j = 0; j < m_Graph.m_nVexNum; j++)
		{
			cout << left<<setw(4)<<m_Graph.m_aAdjMatrix[i][j] << "    ";
		}
		cout << endl;
	}
}

int main()
{
    cout << "=========������Ϣ����ϵͳ=========="<<endl;
	cout << "1.������������ͼ" << endl;
	cout << "2.��ѯ������Ϣ" << endl;
	cout << "3.���ξ��㵼��" << endl;
	cout << "4.�������·��" << endl;
	cout << "5.�����·�滮" << endl;
	cout << "0.�˳�" << endl;
   
	//information();
	int choose;

	do {
		cout << "����ѡ���ܣ�";
		cin >> choose;
		switch (choose)
		{
		case 1:
			CreatGraph();
			cout << "�����ɹ���"<<endl;
			cout << "==================="<<endl;
			continue;
		case 2:
			GetSpotInfo();

			cout <<endl<< "===================" << endl;
			continue;
		case 3:
			TravelPath();

			cout << endl << "===================" << endl;
			continue;
		case 4:
            ShortPath();

			cout << endl << "===================" << endl;
			continue;
		case 5:
			ElectricPath();

			cout << endl << "===================" << endl;
			continue;
		case 0:
			cout << "��лʹ�ñ�ϵͳ��";
		}
	}while(choose != 0);
	system("pause");


}

