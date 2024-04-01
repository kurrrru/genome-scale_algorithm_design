#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool	check_hamilton_list(int N, vector<vector<int> > adjadency_list, vector<int> certificate_path)
{
	vector<bool>	visited(N, false);
	for (int i = 0; i < (int)adjadency_list.size(); i++)
		sort(adjadency_list[i].begin(), adjadency_list[i].end());
	for (int i = 0; i < (int)certificate_path.size(); i++)
	{
		if (visited[certificate_path[i]])
			return (false);
		if (i > 0)
		{
			auto	it = lower_bound(adjadency_list[certificate_path[i - 1]].begin(), adjadency_list[certificate_path[i - 1]].end(), certificate_path[i]);
			if (it == adjadency_list[certificate_path[i - 1]].end() || *it != certificate_path[i])
				return (false);
		}
		visited[certificate_path[i]] = true;
	}
	for (int i = 0; i < N; i++)
		if (!visited[i])
			return (false);
	return (true);
}

int	main(void)
{
	int						N = 5;
	vector<vector<int> >	adjadency_list = {
		{1, 2, 4},
		{0, 2, 3, 4},
		{0, 1, 3},
		{1, 2, 4},
		{1, 3}
	};
	vector<int>				certificate_path = {0, 1, 2, 3, 4};
	cout << check_hamilton_list(N, adjadency_list, certificate_path) << endl;
}
