#include <iostream>
using namespace std;

int i, j, n;
double h;
double x[100];
double y[100];

int main()
{
	cout << "please input n ";
	cin >> n;
	cout << "please input x,y��" << endl;
	for (i = 0; i < n; i++) {
		cin >> x[i];
		cin >> y[i];
	}
	cout << "��x=" << x[0] << "��x=" << x[n - 1] << "�Ļ���" << endl;
	h = (x[n - 1] - x[0]) / (n - 1);
	cout << "����h=" << h<<endl;
	double res = 0;
	res = y[0] + y[n - 1];
	for (i = 1; i < n - 1; i++)
	{
		res += 2 * y[i];
	}
	res *= h / 2;
	cout  << res << endl;
	system("pause");
}