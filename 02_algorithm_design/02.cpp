#include<iostream>
#include<string>
#include<vector>

using namespace std;

int	KMP(string T, string p, vector<int> &fail)
{
	for (int i = 0, j = 0; i < T.size(); i++, j++)
	{
		if (T[i] == p[j] && j == p.size() - 1)
			return (i - j);
		while (j > 0 && T[i] != p[j])
			j = fail[j - 1];
	}
	return (-1);
}

void	calc_fail(string p, vector<int> &fail)
{
	vector<int> sub(p.size(), 0);
	for (int i = 0; i < p.size(); i++)
		fail[i] = 0;
	for (int i = 1, j = 0; i < p.size(); i++)
	{
		while (j > 0 && p[i] != p[j])
			j = sub[j - 1];
		if (p[i] == p[j])	
			sub[i] = ++j;
		if (p[i] == p[j] && (j == p.size() - 1 || p[i + 1] != p[j + 1]))
			fail[i] = j;
	}
}


int main()
{
	string T; // = "ATADDAAATA";
	string p; // = "D";
	cin >> T >> p;
	vector<int> fail(p.size(), 0);
	// int fail[10] = {1, 0, 0, 0, 0, 1, 1, 1, 2, 0};
	calc_fail(p, fail);
	// for (int i = 0; i < p.size(); i++)
	// 	cout << fail[i] << " ";
	// cout << endl;
	cout << KMP(T, p, fail) << endl;
}
