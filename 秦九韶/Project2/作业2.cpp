#include<iostream>
#include <stdlib.h>
using namespace std;
int main()
{
	int i;
	int n;
	int j;
	double x;
	double p = 0;
	double y = 1;
	cout << "���������n��";
	cin >> n;
	cout << endl;
	cout << "������x��";
	cin >> x;
	double *a = new double[n];
	for (i = 0; i < n; i++)
	{
		cout << "�������" << i << "ϵ��" << endl;
		cin >> a[i];
	}
	for (i = 0; i < n; i++)
	{
		p = (p*x) + a[i];
	}
	cout << "���p�ǣ�" << p;
	cout << endl;
	system("pause");
	return 0;

}
