#pragma once
#include <vector>
#include <list>
#include <iostream>
using namespace std;

class Graph
{
private:
	const int nulledge = -1;

	class Edge
	{
	public:
		int source, destination;
		int weight;
		Edge(int src, int des, int w) : source(src), destination(des), weight(w) {}
	};
	int numOfVertices;
	vector<vector<int>> adjacencyList;
	vector<bool> visited;

	bool badIndex(size_t i, size_t j)
	{
		return i < 0 ||
			j < 0 ||
			i >= numOfVertices ||
			j >= numOfVertices;
	}

	bool validateNewEdge(size_t i, size_t j)
	{
		if (adjacencyList[i][j] != nulledge)
		{
			cerr << "Edge already exists.\n";
			return false;
		}
		if (badIndex(i, j))
		{
			cerr << "Invalid edge.\n";
			return false;
		}
		return true;
	}

	void init_bool_vector_false(vector<bool>& v)
	{
		for (int i = 0; i < v.size(); i++)
			v[i] = false;
	}

public:
	Graph(int count);
	void addEdge(Edge edge);
	void addEdge(size_t i, size_t j);
	void BFS(int start);
	void DFS(int start);
	void printMatrix();
};

Graph::Graph(int count) :
	numOfVertices(count),
	adjacencyList(count, vector<int>(count, nulledge)),
	visited(count, false)
{}

void Graph::addEdge(Edge edge)
{
	size_t i = edge.source - 1,
		j = edge.destination - 1;
	if (validateNewEdge(i, j) == false)
	{
		cerr << "Cannot add edge from " << i << " to " << j << ". Terminating...\n";
		return;
	}
	adjacencyList[i][j] = 1;
	cout << "Added edge from " << i << " to " << j << ".\n";
}

void Graph::addEdge(size_t i, size_t j)
{
	if (validateNewEdge(i, j) == false)
	{
		cerr << "Cannot add edge from " << i << " to " << j << ". Terminating...\n";
		return;
	}
	cout << "Adding edge from " << i << " to " << j << ".\n";;
	adjacencyList[i][j] = 1;
}

void Graph::BFS(int start)
{
	init_bool_vector_false(visited);
	list<int> queue;

	visited[start] = true;
	queue.push_back(start);

	while (!queue.empty())
	{
		start = queue.front();
		cout << start << " ";
		queue.pop_front();

		for (int i = 0; i < numOfVertices; i++)
		{
			if (visited[i] || adjacencyList[start][i] == nulledge) continue;
			visited[i] = true;
			queue.push_back(i);
		}
	}
	cout << "\n";
}

void Graph::DFS(int start)
{
	visited[start] = true;
	cout << start << " ";
	for (int i = 0; i < numOfVertices; i++)
		if (!visited[i] && adjacencyList[start][i] != nulledge) DFS(i);
}

void Graph::printMatrix()
{
	cout << "Adjacency Matrix:\n";
	for (size_t i = 0; i < numOfVertices; i++)
	{
		for (size_t j = 0; j < numOfVertices; j++)
		{
			if (adjacencyList[i][j] == nulledge) { cout << "n" << "\t"; continue; }
			cout << adjacencyList[i][j] << "\t";
		}
		cout << "\n";
	}
}