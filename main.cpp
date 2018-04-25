#include <bits/stdc++.h>
#define int long long

int dp[100][100][100];
int solve(int a, int b int c)
{
	if(a < 0 || b < 0 || c < 0) 
		return -10000;
	int re = 0;
	int &ret = dp[a][b][c];
	if(ret != -1) 
		return ret;
	re = max(re, 1 + solve(a-3,b,c));
	re = max(re, 1 + solve(a,b-3,c));
	re = max(re, 1 + solve(a,b,c-3));
	re = max(re, 1 + solve(a-1,b-1,c-1));
	ret = re; 
	return ret;
}
int main()
{
	for(int i=0;i<1)
	int a, b, c; 
	cin >> a >> b >> c;
	
	int af = a/3;
	a = a%3;
	while(a < 10 && af > 0)
	{
		a += 3;
		af--;
	}int bf = b/3;
	b = b%3;
	while(b < 10 && bf > 0)
	{
		b += 3;
		bf--;
	}int cf = c/3;
	c = c%3;
	while(b < 10 && cf > 0)
	{
		c += 3;
		cf--;
	}
	cout << af + bf + cf + solve(a,b,c) << endl;


	return 0
}