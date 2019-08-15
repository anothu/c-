#include "stdafx.h"
#include <string>
#include"cardList.h"
#include<iostream>
#include"global.h"
#include"model.h"
#include"tool.h"

using namespace std;

void outputStatisticsMenu(){
	cout << "--------��ѯͳ�Ʋ˵�--------" << endl << endl;
	cout << "1.�������" << endl;
	cout << "2.�ϻ��»����" << endl;
	cout << "3.��ֵ�˷����" << endl;
	cout << "0.�˳�" << endl << endl;
	cout << "��ѡ��˵����ţ�0~3����";
}

void outputMenu()
{

	cout << "---------�Ʒ�ϵͳ�˵�---------" << endl << endl;
	cout << "1.��ӿ�" << endl;
	cout << "2.��ѯ��" << endl;
	cout << "3.�ϻ�" << endl;
	cout << "4.�»�" << endl;
	cout << "5.��ֵ" << endl;
	cout << "6.�˷�" << endl;
	cout << "7.��ѯͳ��" << endl;
	cout << "8.ע����" << endl;
	cout << "0.�˳�" << endl << endl;

	cout << "��ѡ��˵����ţ�0~8����";

}

bool inputCardNo(string& strNo)
{

	while (true)
	{
		cout << "�����뿨�ţ�����Ϊ1~17����";
		cin >> strNo;
		cin.clear();
		cin.sync();
		if (strNo.length() >= 17)
		{
			cout << "���ų��ȳ������ֵ��" << endl;

			char ch = 'M';
			while (ch != 'N'&&ch != 'Y')
			{
				cout << "���������𣿣�y/n��";
				cin >> ch;
				ch = toupper(ch);
				cin.ignore(1000, '\n');
			}
			if (ch == 'N')
			{
				return false;
			}
		}
		else
		{
			break;
		}
	}
}

bool inputCardPwd(string& strPwd)
{

	while (true)
	{
		cout << "���������룺";
		cin >> strPwd;
		if (strPwd.length() <= 6)
		{
			cout << "���벻��������λ" << endl;
			char ch = 'M';
			while (ch != 'N'&&ch != 'Y')
			{
				cout << "���������𣿣�y/n��";
				cin >> ch;
				ch = toupper(ch);
				cin.ignore(1000, '\n');
			}

			if (ch == 'N')
			{
				return false;
			}
		}
		else
		{
			break;
		}
	}
}

bool inputCardBalance(float& fbalance)
{

	while (true)
	{
		cout << "�������";
		cin >> fbalance;
		if (fbalance <3)
		{
			cout << "����С����Ԫ" << endl;
			char ch = 'M';
			while (ch != 'N'&&ch != 'Y')
			{
				cout << "���������𣿣�y/n��";
				cin >> ch;
				ch = toupper(ch);
				cin.ignore(1000, '\n');
			}
			if (ch == 'N')
			{
				return false;
			}
		}
		else
		{
			break;
		}
	}
}

bool inputNoPwd(string& strNo, string& strPwd)
{
	if (!inputCardNo(strNo))
	{
		return false;
	}
	if (!inputCardPwd(strPwd))
	{
		return false;
	}
	return true;
}

bool inputNoPwdBalance(string& strNo, string& strPwd, float& fBalance)
{

	if (!inputCardNo(strNo))
	{
		return false;
	}
	if (!inputCardPwd(strPwd))
	{
		return false;
	}
	if (!inputCardBalance(fBalance))
	{
		return false;
	}

	return true;
}

