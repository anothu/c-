#include<iostream>
using namespace std;

int n = 0;
int p = 1;
int c = 2;

double f(double x, double y)
{
	return y - (2 * x / y);//����ģ��
}
int main()
{
	double x, y[99][3], h;
	int N;
	cout << "������y0 ";
	cin >> y[0][n];
	cout << "�����벽��h "; 
	cin >> h;
	cout << "������N "; 
	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		x = (i - 1)*h;
		y[i][p] = y[i-1][n]+h*f(x, y[i-1][n]);
		y[i][c] = y[i - 1][n] + h*f(x + h, y[i][p]);
		y[i][n] = (y[i][p] + y[i][c]) / 2;
		cout << y[i][n] << endl;
	}
	system("pause");
}