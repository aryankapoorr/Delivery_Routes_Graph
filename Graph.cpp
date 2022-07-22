/******************************************************************************

Aryan Kapoor

*******************************************************************************/
// Imports and declarations below
#include "Graph.h"

/*
* Default constructor, sets the size of the graph to 0
*/
Graph::Graph() {
	size = 0;
}

/*
* Overloaded constructor, sets the size of the graph to the parameter given
*/
Graph::Graph(int s) {
	size = s;
}

/*
* Inserts a vertex into the graph, adding the vertex to the vector of vertex names,
* as well as creating a vector for the vertex in the adjacency list, while also
* increasing the size attribute
*/
void Graph::insertVertex(std::string s) {
	std::pair<std::string, int> name = { s, size };
	names.push_back(name);

	std::vector<struct Edge> row;
	graph.push_back(row);

	size++;
}

/*
* Deletes a vertex from the graph, removing it from the vector of vertex names,
* as well as removing it's vector row from the adjacency list, while decrementing
* the size attribute
* 
* Returns the vector of Edge structs containing the vertex's row in the adjacency list
*/
std::vector<struct Edge> Graph::deleteVertex(std::string s) {
	int index = 0;

	// Iterates through the names vertex to find the index of the spot of deletion
	for (auto& it : names) {
		std::string check = it.first;
		if (check == s)
			index = it.second;
	}

	// Uses an iterator to delete the vertex from the proper index in the names vector
	std::vector<std::pair<std::string, int>>::iterator it;
	it = names.begin() + index;
	names.erase(it);

	// Uses an iterator to delete the vertex from the proper index in the adjacency list
	std::vector<std::vector<struct Edge>>::iterator iter;
	iter = graph.begin() + index;
	graph.erase(iter);
	size--;

	return graph[index];
}

/*
* Inserts an edge into the adjacency list, based on the starting location, 
* ending location, and weight
*/
void Graph::insertEdge(std::string start, std::string end, int weight) {
	// Creates an Edge struct to add to the adjacency list, based on the
	// values of the parameters
	struct Edge add;
	add.setDest(end);
	add.setWeight(weight);

	int index = 0;

	// Iterates through the names vector to find the proper spot of insertion, 
	// then adding it to the vector
	for (int i = 0; i < size; i++) {
		std::string test = names[i].first;
		if (test == start)
			index = i;
	}

	graph[index].push_back(add);
}

/*
* Deletes an edge from the adjacency list, based on the starting and ending locations given,
* returns a pair which contains the value of the ending location and weight removed
*/
std::pair<std::string, int> Graph::deleteEdge(std::string start, std::string end) {
	int index = 0;
	std::pair<std::string, int> output;

	// Iterates through the names vector to find the proper row of deletion
	for (int i = 0; i < size; i++) {
		std::string test = names[i].first;
		if (test == start)
			index = i;
	}

	long len = graph[index].size();

	// Iterates through the specific row in the adjacency list, finding the exact
	// spot of deletion
	for (long i = 0; i < len; i++) {
		std::string test = graph[index][i].getDest();
		if (test == end) {
			// Stores the values being removing before erasing it from the vector
			output.first = graph[index][i].getDest();
			output.second = graph[index][i].getWeight();
			graph[index].erase(graph[index].begin() + i);
		}
	}

	return output;
}

/*
* Determines the weight of a path in the graph based off of the starting
* and ending location, returning the weight of the edge and -1 
* if the path does not exist in the graph
*/
int Graph::pathWeight(std::string start, std::string end) {
	int index = -1;
	int edge = -1;

	// Iterates through the names vector to find the starting point of the Edge
	for (int i = 0; i < size; i++) {
		std::string test = names[i].first;
		if (test == start)
			index = i;
	}

	// Sets the index to -1 if the starting point does not exist in the graph
	if (index == -1)
		edge = -1;

	long len = graph[index].size();

	// Iterates through the row in the adjacency list to find the matching Edge
	for (long i = 0; i < len; i++) {
		std::string test = graph[index][i].getDest();

		// Iterates through the conditional if the ending location matches the parameter,
		// setting the edge to the weight, and -1 if there is no match
		if (test == end) {
			if (graph[index][i].getWeight())
				edge = graph[index][i].getWeight();
			else if (graph[index][i].getWeight() == 0)
				edge = 0;
			else
				edge = -1;
		}
	}

	return edge;
}

/*
* Overloaded less than operator for the Edge struct, based off of the
* weight of the edge, using the name of the ending location as a tie breaker
*/
bool Edge::operator<(const Edge& e) {
	if (weight < e.weight)
		return true;
	else if (weight == e.weight) {
		if (dest < e.dest)
			return true;
		else
			return false;
	}
	else
		return false;
}

/*
* Overloaded greater than operator for the edeg struct, based off of the
* weight of the edge, using the name of the ending location as a tie breaker
*/
bool Edge::operator>(const Edge& e) {
	if (weight > e.weight)
		return true;
	else if (weight == e.weight) {
		if (dest > e.dest)
			return true;
		else
			return false;
	}
	else
		return false;
}

Graph::HashMap::HashMap() {
	hashSize = 5;
	table = new std::list<std::pair<int, std::string>>[5];
}

Graph::HashMap::HashMap(int size) {
	hashSize = size;
	table = new std::list<std::pair<int, std::string>>[size];
}

void Graph::HashMap::insertHash(std::string s) {
	int i = reHash(size);
}