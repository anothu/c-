#include<iostream>
#include<fstream>
#include<string>
using namespace std;


int n, k,b;
int a[44];
int dp[44][10];//ǰi�����м���j���˺�   
int m[44][44];
int t;
void prepare()
{
	for (int i = 1; i <= n; i++)m[i][i] = a[i];
	for (int i = 1; i <= n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			m[i][j] = m[i][j - 1] * 10 + m[j][j];
		}
	}
}


int max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}


int main()
{
	ifstream myfile("F:\max_k_in.txt");
	ofstream outfile("F:\max_k_out.txt");
	myfile >> n;
	myfile >> k;
	myfile >> b;
	for (int i = n; i >= 1; i--)
	{
		a[i] = b % 10;
		b = b / 10;
	}
	prepare();
	//��̬�滮
	for (int i = 1; i <= n; i++)//ö��ǰi������   
	{
		for (int j = 0; j<i; j++)//ö�ٳ˺Ÿ���  
		{
			if (j == 0)
			{
				dp[i][j] = m[1][i]; continue;
			}
			for (int k = 1; k<i; k++)//ö�ٳ˺�λ��   
			{ 
				dp[i][j] = max(dp[i][j], dp[k][j - 1] * m[k + 1][i]);		
			}	
		}
	}
	outfile << dp[n][k-1];
	cout << dp[n][k - 1];
	system("pause");
}
//dp[i][0] = m[1][i];��j=0��
//dp[i][j] = max(dp[i][j], dp[k][j - 1] * m[k + 1][i]);(0<j<i)