#include <iostream>
#include<iomanip>
#include<fstream>
#include"student.h"
using namespace std;
ofstream f1("stud.dat", ios::trunc);
int main()
{
	student stu[10];
	int choice;
	int s = 0;
	int n;
	cout << "������ѧ������:" << endl;
	cin >> n;
	while (s == 0)
	{
		menu();
		cout << "���������ѡ��:" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			input(n, stu);
			break;
		case 2:
			output(n, stu);
			break;
		case 3:
			search(n, stu);
			break;
		default:
			s = 1;
		}
	}
}
