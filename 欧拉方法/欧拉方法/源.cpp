#include<iostream>
using namespace std;

double f(double x, double y)
{
	return y-(2 * (x/ y));
}
int main()
{
    double y[999];
	cout << "�����벽����";
    double h;
	cin >> h;
	cout << "������Ҫ��n: ";
	int n;
	cin >> n;
	cout << "������y[0]: ";
	cin >> y[0];
	double x;
	for(int i=1;i<=n;i++)
	{
		x = (i - 1)*h;
		y[i] = y[i - 1] + h*f(x,y[i-1]);
		cout << "y[" << i << "] : " << y[i]<<endl;
	}
	system("pause");
}