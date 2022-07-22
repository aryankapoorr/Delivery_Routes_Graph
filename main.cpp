/******************************************************************************

Aryan Kapoor

Truck delivery routes optimized and sorted in a graphical representation.

*******************************************************************************/
// Imports and declarations below
#include <iostream>
#include <fstream>
#include <sstream>
#include "Graph.h"

using namespace std;

// Function prototypes below
void readGraphFile(Graph&, string);
struct Edge readRoutesFile(Graph&, string);
void outputData(vector<struct Edge>);

/*
* Main function, serves as the driver for the program
*/
int main() {
	// Sets the initial graph and route list used to output information
	Graph g;
	vector<struct Edge> routeList;

	// Reads in and stores the file names
	ifstream file1, file2;
	string input1, input2;
	cin >> input1 >> input2;

	// Opens the 2 files
	file1.open(input1);
	file2.open(input2);

	// Iterates if the graph file opens properly
	if (file1.is_open()) {
		string nextLine1;

		// Reads through each line of the file, calling the readGraphfile
		// method to build the graph
		while (getline(file1, nextLine1)) {
			if (nextLine1 != "")
				readGraphFile(g, nextLine1);
		}
	}

	// Iterates if the routes file opens properly
	if (file2.is_open()) {
		string nextLine2;

		// Reads through each line of the file, calling the readRoutesFile
		// method to store route information in the routeList vector
		while (getline(file2, nextLine2)) {
			if (nextLine2 != "")
				routeList.push_back(readRoutesFile(g, nextLine2));
		}
	}

	// Outputs the data based on the information in the route list
	outputData(routeList);

	// Closes the 2 files, closes the program
	file1.close();
	file2.close();
	return 0;
}

/*
* Reads through the file line, inputting the information into the
* graph, creating the vertex and its routes in the adjacency list
*/
void readGraphFile(Graph& g, string line) {
	// Uses a stringstream to read through the file, stores the vertex
	string name, next;
	stringstream ss(line);
	ss >> name;
	g.insertVertex(name);

	// Reads through each route remaining in the file
	while (ss >> next) {
		// Parses through and stores the weight and ending location of each routes
		long comma = next.find(",");
		string edge = next.substr(0, comma);
		int num = stoi(next.substr(comma + 1));
		g.insertEdge(name, edge, num);
	}
}

/*
* Reads through a line of the routes file, determining the
* weight of a given route and returning an Edge struct, containing
* the final weight of the route (0 if no route exists) and the name of
* the driver of the route
*/
struct Edge readRoutesFile(Graph& g, string line) {
	// Creates a vector of names of locations, using a stringstream
	// to read through the line
	bool valid = true;
	int weight = 0;
	string driver, next;
	vector<string> names;
	stringstream ss(line);
	ss >> driver;

	// Adds the locations on the route to the list
	while (ss >> next)
		names.push_back(next);

	long len = names.size() - 1;

	// Reads through the names vector, determining the weight of each stop in the route
	for (long i = 0; i < len; i++) {
		string first = names[i];
		string second = names[i + 1];
		int edge = g.pathWeight(first, second);

		// If the route does not exist make sure that the line is invalid and set the weight to 0
		if (edge == -1)
			valid = false;
		// Otherwise, add the corresponding edge to the total weight of the route
		else
			weight += edge;
	}

	// Sets the weight of the total route to 0 if the route is not valid
	if (!valid)
		weight = 0;

	// Creates a struct to return the driver name and route
	struct Edge e; 
	e.setDest(driver);
	e.setWeight(weight);

	return e;
}

/*
* Outputs the routes based on the vector parameter, utilizing an insertion sort
* to properly display the drivers and routes in order
*/
void outputData(vector<struct Edge> list) {
	long size = list.size();
	struct Edge key;
	long j;

	// Insertion sort to sort the values of the list vector
	for (long i = 1; i < size; i++) {
		key = list[i];
		j = i - 1;

		while (j >= 0 && list[j] > key) {
			list[j + 1] = list[j];
			j--;
		}
		list[j + 1] = key;
	}

	// Reads through the sorted list vector, outputting the driver name and weight,
	// as well as whether or not the route is valid or invalid
	for (long i = 0; i < size; i++) {
		cout << list[i].getDest() << "\t" << list[i].getWeight() << "\t";

		// If the weight of the route is 0, the route is invalid
		if (list[i].getWeight() == 0)
			cout << "invalid" << endl;
		else
			cout << "valid" << endl;
	}
}