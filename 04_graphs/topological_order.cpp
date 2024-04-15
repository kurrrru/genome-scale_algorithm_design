#include <vector>

void	shortest_path_dag_sub(std::vector<std::vector<int> > &edges, int v, std::vector<bool> &visited, std::vector<int> &order, std::vector<int> &indegree)
{
	int n = (int)edges.size();
	visited[v] = true;
	order.push_back(v);
	for (int i = 0; i < (int)edges[v].size(); i++)
	{
		indegree[edges[v][i]]--;
		if (indegree[edges[v][i]] == 0 && !visited[edges[v][i]])
			shortest_path_dag_sub(edges, edges[v][i], visited, order, indegree);
	}
}

std::vector<int>	shortest_path_dag(std::vector<std::vector<int> > &edges)
{
	int n = (int)edges.size();
	std::vector<int> order;
	std::vector<bool> visited(n, false);
	std::vector<int> indegree(n, 0);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < (int)edges[i].size(); j++)
			indegree[edges[i][j]]++;
	for (int i = 0; i < n; i++)
		if (indegree[i] == 0 && !visited[i])
			shortest_path_dag_sub(edges, i, visited, order, indegree);
	return (order);
}

#include <iostream>
int	main(void)
{
	std::vector<std::vector<int> > edges = {
		{1, 2, 3},
		{2, 4, 5},
		{4},
		{4},
		{},
		{}
	};
	std::vector<int> order = shortest_path_dag(edges);
	for (int i = 0; i < (int)order.size(); i++)
		std::cout << order[i] << " ";
	std::cout << std::endl;
	return (0);
}
