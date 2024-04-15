#include <vector>

void	topological_order_from_vertex(std::vector<std::vector<int> > edges, int v, std::vector<bool> &visited, std::vector<int> &order, std::vector<int> &indegree)
{
	int n = (int)edges.size();
	visited[v] = true;
	order.push_back(v);
	for (int i = 0; i < (int)edges[v].size(); i++)
	{
		indegree[edges[v][i]]--;
		if (indegree[edges[v][i]] == 0 && !visited[edges[v][i]])
			topological_order_from_vertex(edges, edges[v][i], visited, order, indegree);
	}
}

std::vector<int>	topological_order(std::vector<std::vector<int> > edges)
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
			topological_order_from_vertex(edges, i, visited, order, indegree);
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
	std::vector<int> order = topological_order(edges);
	for (int i = 0; i < (int)order.size(); i++)
		std::cout << order[i] << " ";
	std::cout << std::endl;
	return (0);
}
