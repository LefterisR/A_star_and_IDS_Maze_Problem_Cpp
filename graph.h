#pragma once
#include <vector>
#include "spacestate.h"
#include <utility>
//@Author Lefteris Rizos
/*
*Class for UNDIRECTED Graph imprementation
*Graph will define the possible routs that the Robot R can take in the state space, hence going back and forth is possible and allowed 
*/

class Graph
{
private: 
	int dimension;
	int rows;
	int columns;
	int totalNodes;
	int robotNode=-1;
	
public:

	Graph(int dimension,int totalNodes);

	void addEdge(std::vector<std::pair <int, int>> a[],int u, int v, int cost);                         //adds edges to the graph

	void displayGraph(std::vector<std::pair <int, int>> a[]);											//Displayes the elements of the graph, nodes connections with corresponding costs.		

	int getN() { return dimension; }																			

    int getTotalNodes() { return totalNodes; }

	void spaceToGraph(std::vector<std::pair <int, int>> a[], const stateSpace space);                   //main function to translate the given state space to a graph

	int getRobotNode() { return robotNode; }


};