#pragma once
#include <iostream>
#include <vector>
#define nulledge -1
#define MAX INT_MAX
using namespace std;
typedef vector<vector<int>> matrix;
class TravelingSalesperson
{
public:
	TravelingSalesperson(int size);
	TravelingSalesperson(matrix g);
	void solve_tsp(int start_index);
	void print_solution(int start_index);
private:
	size_t numOfNodes;
	int ans;
	matrix graph;
	vector<int> shortest_path, current_path;
	vector<bool> visited;

	void print_current_solution_data(int newCost);
	template<class T>
	void printVector(vector<T> arr);
	bool isVisited(int node_index);
	bool edgeExists(int start_node, int end_node);
	void save_shortest_path_data(int newCost);

	void calculate_shortest_path(int currPos = 0, int counter = 0, int cost = 0);
};

TravelingSalesperson::TravelingSalesperson(int size) : numOfNodes(size),
shortest_path(numOfNodes),
current_path(numOfNodes),
visited(numOfNodes, false),
graph(numOfNodes, vector<int>(numOfNodes, nulledge)),
ans(MAX)
{}

TravelingSalesperson::TravelingSalesperson(matrix g) : numOfNodes(g.size()),
shortest_path(numOfNodes),
current_path(numOfNodes),
visited(numOfNodes, false),
graph(g),
ans(MAX)
{}

void TravelingSalesperson::solve_tsp(int start_index)
{
	visited[start_index] = true;
	calculate_shortest_path(start_index);
	shortest_path.push_back(shortest_path[0]);
}

void TravelingSalesperson::print_solution(int start_index)
{
	cout << "Cost of shortest path: " << ans << "\nShortest path: "; printVector(shortest_path);
}

inline void TravelingSalesperson::print_current_solution_data(int newCost)
{
	cout << "path: "; printVector(current_path); cout << "\tcost: " << newCost << "\n";
}

inline bool TravelingSalesperson::isVisited(int node_index) 
{
	return visited[node_index]; 
}

inline bool TravelingSalesperson::edgeExists(int start_node, int end_node) 
{
	return graph[start_node][end_node] != nulledge;
}

inline void TravelingSalesperson::save_shortest_path_data(int newCost)
{
	ans = newCost;
	for (size_t i = 0; i < numOfNodes; i++)
		shortest_path[i] = current_path[i];
	//cout << "Shortest path now is: "; printVector(shortest_path);  cout << "\tcost: " << ans << "\n";
}

inline void TravelingSalesperson::calculate_shortest_path(int current_node_index, int counter, int cost)
{
	if (cost > ans) return;
	int newCost = 0;
	current_path[counter] = current_node_index + 1;
	if (counter == numOfNodes - 1 && edgeExists(current_node_index,0))
	{
		newCost = cost + graph[current_node_index][0];
		if (newCost < ans) save_shortest_path_data(newCost);
		return;
	}
	current_path[counter] = current_node_index + 1;
	for (int i = 0; i < numOfNodes; i++)
	{
		if (isVisited(i) || !edgeExists(current_node_index, i)) continue;
		
		newCost = cost + graph[current_node_index][i];
		if (newCost > ans) continue;
		visited[i] = true;
		calculate_shortest_path(i, counter + 1, newCost);
		visited[i] = false;
	}
}

template<class T>
inline void TravelingSalesperson::printVector(vector<T> arr)
{
	for (size_t i = 0; i < arr.size(); i++)
	{
		cout << arr[i] << " ";
	}
}
