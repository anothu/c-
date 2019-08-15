#include<iostream>
#include <iomanip>
#include<fstream>
#include"student.h"
using namespace std;
void smallmenu()
{
	cout << "1.����������" << endl;
	cout << "2.��ѧ�Ų���" << endl;
	cout << "���������ѡ��:";
}
void menu()
{
	cout << "1.��������" << endl;
	cout << "2.�������" << endl;
	cout << "3.����������ѧ�Ų���ѧ������" << endl;
	cout << "4.�˳�" << endl;
};
void input(int n, student s[])
{
	ofstream f1("stud.dat", ios::binary || ios_base::out || ios::app);//ofstream ofile(pPath,ios_base::out|ios_base::app|ios_base::binary);
	int i;
	if (!f1.is_open())
	{
		cerr << "�ļ��޷���ȷ��!����д��Ʒ�ϵͳ!" << endl;
		f1.close();
		return;
	}
	for (i = 0; i<n; i++)
	{
		char nu[10];
		cout << "�������" << i + 1 << "��ѧ����ѧ��";
		cin >> nu;
		for (int t = 0; t<10; t++)
		{
			s[i].num[t] = nu[t];
		}
		cout << "�������" << i + 1 << "��ѧ��������";
		cin >> s[i].name;
		cout << "�������" << i + 1 << "��ѧ���ĳɼ�";
		cin >> s[i].grade;
		f1 << s[i].num << " ";
		f1 << s[i].name << " ";
		f1 << s[i].grade << " ";
	}
	f1.close();
}
void output(int n, student s[])
{
	ifstream f1("stud.dat", ios::binary || ios_base::in);
	int i;
	cout << "ѧ��" << "   " << "����" << "    " << "�ɼ�" << endl;
	for (i = 0; i < n; i++)
	{
		char nu[10];
		f1 >> nu;
		for (int t = 0; t < 10; t++)
		{
			s[i].num[t] = nu[t];
		}
		f1 >> s[i].name;
		f1 >> s[i].grade;
		cout << s[i].num << "   ";
		cout << s[i].name << "   ";
		cout << s[i].grade << "   ";
		cout << endl;
	}
}
void save(int n, student s[])
{
	ifstream f1("stud.dat", ios::binary || ios_base::in);
	int i;
	for (i = 0; i < n; i++)
	{
		char nu[10];
		f1 >> nu;
		for (int t = 0; t < 10; t++)
		{
			s[i].num[t] = nu[t];
		}
		f1 >> s[i].name;
		f1 >> s[i].grade;
	}
}
bool equal(char a1[], char a2[], int length)
{
	for (int i = 0; i < length; i++)
		if (a1[i] != a2[i])
			return false;
	return true;
}
void searchbynum(int n, student s[])
{
	save(n, s);
	int i;
	char now_num[10];
	cout << "������Ҫ��ѯ��ѧ����ѧ��:";
	cin >> now_num;
	for (i = 0; i < n; i++)
	{
		if (strcmp(s[i].num, now_num) == 0)
			break;
	}
	cout << "ѧ��" << "   " << "����" << "    " << "�ɼ�" << endl;
	cout << s[i].num << "   ";
	cout << s[i].name << "   ";
	cout << s[i].grade << "   ";
	cout << endl;
}
void searchbyname(int n, student s[])
{
	save(n, s);
	char now_name[10];
	int length, i, j;
	cout << "������Ҫ��ѯ��ѧ��������:";
	cin >> now_name;
	length = strlen(now_name);
	cout << "ѧ��" << "   " << "����" << "    " << "�ɼ�" << endl;
	for (i = 0; i<n; i++)
	{
		if (equal(now_name, s[i].name, length))
		{
			cout << s[i].num << "   ";
			cout << s[i].name << "   ";
			cout << s[i].grade << "   ";
			cout << endl;
		}
	}
}
void search(int n, student s[])
{
	int choice;
	smallmenu();
	cin >> choice;
	if (choice == 1)
		searchbyname(n, s);
	else if (choice == 2)
		searchbynum(n, s);
	else 
		cout << "����ѡ�����!" << endl;
}