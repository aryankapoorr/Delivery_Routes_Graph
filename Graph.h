/******************************************************************************

Aryan Kapoor

*******************************************************************************/
// Imports and declarations below
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <list>
#include <vector>
#include <utility>
#include <string>

struct Edge {
	// Struct attributes
	private:
		std::string dest;
		int weight;

	public:
		// Accessor and mutator for struct destination attribute
		std::string getDest() { return dest; }
		void setDest(std::string s) { dest = s; }
		
		// Accessor and mutator for struct weight attribute
		int getWeight() { return weight; }
		void setWeight(int i) { weight = i; }

		// Overloaded operators comparing two Edge structs
		bool operator<(const Edge&);
		bool operator>(const Edge&);
};

class Graph {
	// Class attributes
	private:
		int size;

		class HashMap {
			const int LOAD_FACTOR = 4;
			int hashSize;
			std::list<std::pair<int, std::string>> *table;

			HashMap();
			HashMap(int);

			void insertHash(std::string);
			void deleteHash(std::string);
			int reHash(int h) { return h % hashSize; }
		};

		// Graph adjacency list is represnted by a vector of Edge struct
		// vectors, with the names of the vertexes stored in their own vector
		std::vector<std::vector<struct Edge>> graph;

		// Names vector contains the name and index of every vertex in the graph
		std::vector<std::pair<std::string, int>> names;

	public:
		// Class constructors
		Graph();
		Graph(int);

		// Size attribute accessor
		int getSize() { return size; }

		// Deletion and insertion methods for a vertex
		void insertVertex(std::string);
		std::vector<struct Edge> deleteVertex(std::string);

		// Deletion and insertion methods for an edge
		void insertEdge(std::string, std::string, int);
		std::pair<std::string, int> deleteEdge(std::string, std::string);

		// Method that returns the weight of an edge, returns -1 if no edge
		int pathWeight(std::string, std::string);
};
#endif