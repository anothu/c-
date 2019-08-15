#include<iostream>
#include<fstream>
#include<string>
using namespace std;


int dp[99][99];

int min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}

int main()
{

	ifstream myfile("F:\ship_in.txt");
	ofstream outfile("F:\ship_out.txt");
	int n;
	myfile >> n;
	for (int i = 1; i < n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			myfile >> dp[i][j];
		}
	}
	//��̬�滮
	for (int k = 2; k<n; k++)//��¼��;����
	{
		for (int i = 1; i <= n - k; i++)//��¼������
		{
			int j = i + k;
			for (int z = i + 1; z <= j; z++)//��¼��תվ
			{				 
				dp[i][j] = min(dp[i][j], dp[i][z] + dp[z][j]);
			}
		}
	}
	cout << dp[1][n];
	outfile << dp[1][n];
}
//min=dp[i][j]
//min=min(dp[i][j],dp[i][z]+dp[z][j])