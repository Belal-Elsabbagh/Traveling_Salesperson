#pragma once
#include <iostream>
#include <vector>
#define nulledge -1
#define INF INT_MAX
using namespace std;
typedef vector<vector<int>> matrix;
class TravelingSalesperson
{
public:
	
	/**
	 * \brief constructs a tsp solver with an empty graph by taking in the number of nodes.
	 * 
	 * \param nNodes The number of nodes in the graph.
	 */
	TravelingSalesperson(int size);
	
	/**
	 * \brief constructs a tsp solver using a given graph.
	 * 
	 * \param g
	 */
	TravelingSalesperson(matrix g);
	
	/**
	 * \brief generates the solution of the shortest path.
	 * 
	 * \param start_index the node to start from
	 */
	void solve_tsp(int start_index);
	
	/**
	 * \brief prints the generated shortest path solution.
	 * 
	 */
	void print_solution();
private:
	size_t numOfNodes;
	int minimum_weight;
	matrix graph;
	vector<int> shortest_path, current_path;
	vector<bool> visited;

	
	/**
	 * \brief prints the current path and its cost.
	 * 
	 * \param newCost the cost of the current path
	 */
	void print_current_solution_data(int newCost);
	
	/**
	 * \brief prints a vector of data.
	 * \tparam T the element type in the vector
	 * \param arr the given vector.
	 */
	template<class T>
	void printVector(vector<T> arr);
	
	
	/**
	 * \brief Checks if node was marked as visited.
	 * 
	 * \param node_index
	 * \return True if node was visited. False otherwise.
	 */
	bool isVisited(int node_index);
	
	/**
	 * \brief Checks to see if edge exists between two nodes.
	 * 
	 * \param start_node_index
	 * \param end_node_index
	 * \return True if an edge exists. False otherwise.
	 */
	bool edgeExists(int start_node, int end_node);
	
	
	void save_shortest_path_data(int newCost);

	bool isPromising(int current_node_index, int next_node_index, int cost);

	/**
	 * \brief calculates the shortest path data and updates it in the shortest path data member of the class..
	 * 
	 * \param current_node_index
	 * \param counter
	 * \param cost
	 */
	void calculate_shortest_path(int currPos = 0, int counter = 0, int cost = 0);
};

TravelingSalesperson::TravelingSalesperson(int nNodes) : numOfNodes(nNodes),
shortest_path(nNodes),
current_path(nNodes),
visited(nNodes, false),
graph(nNodes, vector<int>(nNodes, nulledge)),
minimum_weight(INF)
{}

TravelingSalesperson::TravelingSalesperson(matrix g) : numOfNodes(g.size()),
shortest_path(numOfNodes),
current_path(numOfNodes),
visited(numOfNodes, false),
graph(g),
minimum_weight(INF)
{}

void TravelingSalesperson::solve_tsp(int start_node)
{
	visited[start_node - 1] = true;
	calculate_shortest_path(start_node - 1);
	shortest_path.push_back(shortest_path[0]);
}

void TravelingSalesperson::print_solution()
{
	cout << "Cost of shortest path: " << minimum_weight << "\nShortest path: "; printVector(shortest_path);
}

inline void TravelingSalesperson::print_current_solution_data(int newCost)
{
	cout << "path: "; printVector(current_path); cout << "\tcost: " << newCost << "\n";
}

inline bool TravelingSalesperson::isVisited(int node_index) 
{
	return visited[node_index]; 
}

inline bool TravelingSalesperson::edgeExists(int start_node_index, int end_node_index) 
{
	return graph[start_node_index][end_node_index] != nulledge;
}

inline void TravelingSalesperson::save_shortest_path_data(int newCost)
{
	minimum_weight = newCost;
	shortest_path = vector<int>(current_path);
}

inline bool TravelingSalesperson::isPromising(int current_node_index, int next_node_index, int cost)
{
	if (!edgeExists(current_node_index, next_node_index)) return false;
	return cost < minimum_weight && !isVisited(next_node_index);
}

inline void TravelingSalesperson::calculate_shortest_path(int current_node_index, int counter, int cost)
{
	int newCost = 0;
	current_path[counter] = current_node_index + 1;
	if (counter == numOfNodes - 1 && edgeExists(current_node_index,0))
	{
		newCost = cost + graph[current_node_index][0];
		print_current_solution_data(newCost);
		save_shortest_path_data(newCost);
		return;
	}
	for (int next_node = 0; next_node < numOfNodes; next_node++)
	{
		newCost = cost + graph[current_node_index][next_node];
		if (!isPromising(current_node_index, next_node, newCost)) continue;
		
		visited[next_node] = true;
		calculate_shortest_path(next_node, counter + 1, newCost);
		visited[next_node] = false;
	}
}

template<class T>
inline void TravelingSalesperson::printVector(vector<T> arr)
{
	for (size_t i = 0; i < arr.size(); i++)
		cout << arr[i] << " ";
}
