#include<iostream>
#include <stdlib.h>
using namespace std;
int main()
{
	int i;
	int n;
	int j;
	double x;
	double p=0;
	double y=1;
	cout << "���������n��" ;
	cin >> n;
	cout << endl;
	cout << "������x��";
	cin >> x;
	double *a = new double[n];
	for (i = 0; i < n; i++)
	{
		cout << "�������" << i << "������ʽϵ��" << endl;
		cin >> a[i];
	}
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < i; j++)
		{
			y = y*x;		
		}
		p = p + y*a[i];
		y = 1;
	}
	cout << "���p�ǣ�" << p;
	cout << endl;
	system("pause");
	return 0;

}
