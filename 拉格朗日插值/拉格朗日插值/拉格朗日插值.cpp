#include <iostream>
using namespace std;

int main()
{
	int i, j, n, x1;
	double p, sum;
	cout << "please input n�� ";
	cin >> n;
	double *x = new double[n];
	double *y = new double[n];
	cout << "please input x,y ��" << endl;
	for (i = 0; i < n; i++) {
		cin >> x[i];
		cin >> y[i];
	}
	cout << "����xΪ��ֵ�Ĳ�ֵ��" << endl;
	cin >> x1;
	sum = 0;
	p = 1;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++) {
			if (j != i) {
				p *= (x[i] - x[j]) / (x1 - x[j]);
			}
		}
		sum += y[i] / p;
		p = 1;
	}
	cout << "f��x)��" << x1 << "���Ĳ�ֵΪ��" << sum << endl;
	return 0;
}
