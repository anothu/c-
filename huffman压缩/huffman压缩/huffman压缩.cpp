// Main.cpp: �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include"Compress.h"
#include"Huffman.h"
#include<iomanip>
#include<iostream>
using namespace std;
//#pragma warning(disable:4996)

int main()
{
	char filename[256];
	cout << "========�������ļ�ѹ��=========" << endl;
	cout << "�����ļ�·��:";
	cin >> filename;



	Compress(filename);
	system("pause");
	//getchar();
	return 0;
}
