#include <iostream>
#include <vector>

using namespace std;

bool	check_hamilton_matrix(int N, vector<vector<int>> adjadency_matrix, vector<int> certificate_path)
{
	vector<bool>	visited(N, false);
	for (int i = 0; i < (int)certificate_path.size(); i++)
	{
		if (visited[certificate_path[i]])
			return (false);
		if (i > 0 && adjadency_matrix[certificate_path[i - 1]][certificate_path[i]] == 0)
			return (false);
		visited[certificate_path[i]] = true;
	}
	for (int i = 0; i < N; i++)
		if (!visited[i])
			return (false);
	return (true);
}

int	main(void)
{
	int					N = 5;
	vector<vector<int>>	adjadency_matrix = {
		{0, 1, 1, 0, 1},
		{1, 0, 1, 1, 1},
		{1, 1, 0, 1, 0},
		{0, 1, 1, 0, 1},
		{1, 1, 0, 1, 0}
	};
	vector<int>			certificate_path = {0, 1, 2, 3, 4};
	cout << check_hamilton_matrix(N, adjadency_matrix, certificate_path) << endl;
}
