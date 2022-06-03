#pragma once
#include <iostream>
#include <vector>
#define nulledge -1
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
	bool isVisited_OR_invalidValue(bool visited, int& weight) { return visited || weight == nulledge; }
	void save_shortest_path_data(int newCost);

	void calculate_shortest_path(int currPos = 0, int counter = 1, int cost = 0);
};

TravelingSalesperson::TravelingSalesperson(int size) : numOfNodes(size),
shortest_path(numOfNodes),
current_path(numOfNodes),
visited(numOfNodes, false),
graph(numOfNodes, vector<int>(numOfNodes, nulledge)),
ans(INT_MAX)
{}

TravelingSalesperson::TravelingSalesperson(matrix g) : numOfNodes(g.size()),
shortest_path(numOfNodes),
current_path(numOfNodes),
visited(numOfNodes, false),
graph(g),
ans(INT_MAX)
{}

void TravelingSalesperson::solve_tsp(int start_index)
{
	visited[start_index] = true;
	calculate_shortest_path(start_index);
}

void TravelingSalesperson::print_solution(int start_index)
{
	cout << ans << "\nShortest path: "; printVector(shortest_path); cout << start_index + 1;
}

inline void TravelingSalesperson::print_current_solution_data(int newCost)
{
	cout << "path: "; printVector(current_path); cout << current_path[0]; cout << "\tcost: " << newCost << "\n";
}

inline void TravelingSalesperson::save_shortest_path_data(int newCost)
{
	ans = newCost;
	for (size_t i = 0; i < numOfNodes; i++)
		shortest_path[i] = current_path[i];
	//cout << "Shortest path now is: "; printVector(shortest_path);  cout << "\tcost: " << ans << "\n";
}

inline void TravelingSalesperson::calculate_shortest_path(int currPos, int counter, int cost)
{
	int newCost = 0;
	current_path[counter - 1] = currPos + 1;
	if (counter == numOfNodes && graph[currPos][0])
	{
		newCost = cost + graph[currPos][0];
		if (newCost < ans) save_shortest_path_data(newCost);
		//cout << "-------------------------------------------\n";
		return;
	}
	for (int i = 0; i < numOfNodes; i++)
	{
		if (isVisited_OR_invalidValue(visited[i], graph[currPos][i])) continue;
		
		newCost = cost + graph[currPos][i];
		if (newCost > ans) continue;
		
		visited[i] = true;
		calculate_shortest_path(i, counter + 1, newCost);
		visited[i] = false;
	}
}

template<class T>
inline void TravelingSalesperson::printVector(vector<T> arr)
{
	for (T& i : arr)
	{
		cout << i << " ";
	}
}
