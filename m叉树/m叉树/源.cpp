#include<iostream>
#define MAXSIZE 150
using namespace std;
int main()
{
	int n, m, d;
	int d_now = 0;//��ǰ�ܼ�ֵ 
	int w_now = 0;//��ǰ���� 
	int w_min = 100;//��С���� 
	cin >> n;
	cin >> m;
	cin >> d;
	int w[MAXSIZE][MAXSIZE];
	int c[MAXSIZE][MAXSIZE];
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			cin >> w[i][j];
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			cin >> c[i][j];
		}
	}
	int p[MAXSIZE];//�洢��������Ӧ��Ӧ�̱��
	int pmin[MAXSIZE];//�洢��С������Ӧ��Ӧ�̱�� 
	for (int i = 1; i <= n; i++)
		p[i] = 0;
	int t = 1;//�� 
	int q = 1;//�� 
	while (t>0)
	{


		if (d_now + c[t][q]>d)
		{
			if (q<m)                //��һ����Ӧ�� 
				q++;
			else                //��һ������ 
			{
				t--;
				d_now -= c[t][p[t]];
				w_now -= w[t][p[t]];
				while (p[t] >= m)
				{
					t--;
					d_now -= c[t][p[t]];
					w_now -= w[t][p[t]];
					if (t <= 0)
						break;
				}
				q = p[t] + 1;
			}
		}
		else
		{
			d_now += c[t][q];
			w_now += w[t][q];

			p[t] = q;
			if (t == n)//�ѵ����һ������ 
			{
				if (w_now<w_min)
				{
					for (int i = 1; i <= n; i++)
						pmin[i] = p[i];
					w_min = w_now;

				}
				if (q<m)
				{
					w_now -= w[t][q];
					d_now -= c[t][q];
					q++;
				}
				else
				{

					d_now -= c[t][p[t]];
					w_now -= w[t][p[t]];
					t--;

					d_now -= c[t][p[t]];
					w_now -= w[t][p[t]];

					while (p[t] >= m)
					{
						
						d_now -= c[t][p[t]];
						w_now -= w[t][p[t]];
						t--;
						if (t <= 0)
							break;
					}
					q = p[t] + 1;
				}
			}
			else//δ�����һ������ 
			{
				t++;
				q = 1;
			}
		}

	}
	for (int i = 1; i<n; i++)
	{
		cout << pmin[i] << " ";
	}
	cout << pmin[n];
	cout << endl;
	cout << w_min;
	return 0;
}