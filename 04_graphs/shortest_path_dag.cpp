#include <vector>
#include <iostream>

const int INF = 1 << 30;

void	shortest_path_dag_sub(std::vector<std::vector<int> > &cost, int v, std::vector<int> &distance, std::vector<int> &indegree)
{
	std::cout << "v: " << v << std::endl;
	int n = (int)cost.size();
	for (int i = 0; i < n; i++)
	{
		if (cost[v][i] == INF)
			continue;
		distance[i] = std::min(distance[i], distance[v] + cost[v][i]);
		indegree[i]--;
		if (indegree[i] == 0)
			shortest_path_dag_sub(cost, i, distance, indegree);
	}
}

void	shortest_path_dag(std::vector<std::vector<int> > &cost, int s, std::vector<int> &distance)
{
	int n = (int)cost.size();
	std::vector<int> indegree(n, 0);
	distance[s] = 0;
	indegree[s] = -1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (cost[i][j] != INF)
				indegree[j]++;
	shortest_path_dag_sub(cost, s, distance, indegree);
}

int	main(void)
{
	std::vector<std::vector<int> > cost = {
		{INF, 3, INF, 4, 6, INF},
		{INF, INF, 4, -1, INF, 4},
		{INF, INF, INF, INF, INF, INF},
		{INF, INF, INF, INF, INF, 3},
		{INF, INF, INF, INF, INF, 1},
		{INF, INF, INF, INF, INF, INF}
	};
	std::vector<int> distance(6, INF);
	shortest_path_dag(cost, 0, distance);
	for (int i = 0; i < (int)distance.size(); i++)
		std::cout << distance[i] << " ";
	std::cout << std::endl;
	return (0);
}
