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
	void print_solution();
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

/**
 * \brief constructs a tsp solver with an empty graph by taking in the number of nodes.
 * 
 * \param nNodes The number of nodes in the graph.
 */
TravelingSalesperson::TravelingSalesperson(int nNodes) : numOfNodes(nNodes),
shortest_path(nNodes),
current_path(nNodes),
visited(nNodes, false),
graph(nNodes, vector<int>(nNodes, nulledge)),
ans(MAX)
{}

/**
 * \brief constructs a tsp solver using a given graph.
 * 
 * \param g
 */
TravelingSalesperson::TravelingSalesperson(matrix g) : numOfNodes(g.size()),
shortest_path(numOfNodes),
current_path(numOfNodes),
visited(numOfNodes, false),
graph(g),
ans(MAX)
{}

/**
 * \brief generates the solution of the shortest path.
 * 
 * \param start_index the node to start from
 */
void TravelingSalesperson::solve_tsp(int start_node)
{
	visited[start_node - 1] = true;
	calculate_shortest_path(start_node - 1);
	shortest_path.push_back(shortest_path[0]);
}

/**
 * \brief prints the generated shortest path solution.
 * 
 */
void TravelingSalesperson::print_solution()
{
	cout << "Cost of shortest path: " << ans << "\nShortest path: "; printVector(shortest_path);
}

/**
 * \brief prints the current path and its cost.
 * 
 * \param newCost the cost of the current path
 */
inline void TravelingSalesperson::print_current_solution_data(int newCost)
{
	cout << "path: "; printVector(current_path); cout << "\tcost: " << newCost << "\n";
}

/**
 * \brief Checks if node was marked as visited.
 * 
 * \param node_index
 * \return True if node was visited. False otherwise.
 */
inline bool TravelingSalesperson::isVisited(int node_index) 
{
	return visited[node_index]; 
}

/**
 * \brief Checks to see if edge exists between two nodes.
 * 
 * \param start_node_index
 * \param end_node_index
 * \return True if an edge exists. False otherwise.
 */
inline bool TravelingSalesperson::edgeExists(int start_node_index, int end_node_index) 
{
	return graph[start_node_index][end_node_index] != nulledge;
}

inline void TravelingSalesperson::save_shortest_path_data(int newCost)
{
	ans = newCost;
	for (size_t i = 0; i < numOfNodes; i++)
		shortest_path[i] = current_path[i];
}

/**
 * \brief calculates the shortest path data and updates it in the shortest path data member of the class..
 * 
 * \param current_node_index
 * \param counter
 * \param cost
 */
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

/**
 * \brief prints a vector of data.
 * \tparam T the element type in the vector
 * \param arr the given vector.
 */
template<class T>
inline void TravelingSalesperson::printVector(vector<T> arr)
{
	for (size_t i = 0; i < arr.size(); i++)
		cout << arr[i] << " ";
}
