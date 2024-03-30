#include<iostream>
#include<string>
#include<vector>

using namespace std;

int	MP(string T, string p, vector<int> &fail)
{
	int i = 0;
	int j = 0;
	while (i < T.size())
	{
		if (T[i] == p[j])
		{
			i++;
			j++;
			if (j == p.size())
				return (i - j);
		}
		else
		{
			if (j != 0)
				j = fail[j];
			else
				i++;
		}
	}
	return (-1);
}

void	calc_fail(string T, vector<int> &fail)
{
	int i = 1;
	int j = 0;
	fail[0] = 1;
	while (i < T.size())
	{
		if (T[i] == T[j])
		{
			fail[i] = j + 1;
			i++;
			j++;
		}
		else
		{
			if (j != 0)
				j = fail[j];
			else
				i++;
		}
	}
	
}

int main()
{
	string T; //  = "ATADDAAATA";
	string p; // = "D";
	cin >> T >> p;
	vector<int> fail(T.size(), 0);
	// int fail[10] = {1, 0, 0, 0, 0, 1, 1, 1, 2, 0};
	calc_fail(T, fail);
	for (int i = 0; i < fail.size(); i++)
		cout << fail[i] << " ";
	cout << MP(T, p, fail) << endl;
}
