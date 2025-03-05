
#ifndef SEARCHTREE_H
#define SEARCHTREE_H


#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <utility>
//@Author Lefteris Rizos
/*
* Class Node
* Each node is an objected created during the algorith search
* Costitutes a node of te search tree
* contains the vertex number, cost to get there and its depth in the search trees
*/
class Node
{
private:
	int vertex;
	int cost;
	int depth;
public:
	Node(int vertex, int cost, int depth)
	{
		this->vertex = vertex;
		this->cost = cost;
		this->depth = depth;

	}

	//Modifying the standard greater<> element of the priority queue to compare only the costs of the Node objects and give priority to the one with the smaller cost
	bool operator>(const Node& other) const
	{
		
		return cost > other.cost;
	}
	//Accessors 
	int getVertex() const{ return vertex; }
	int getCost() { return cost; }
	int getDepth() { return depth; }
};

std::vector<int> ids(std::vector <std::pair<int, int>> adjacent[], int start, const std::vector<int>& goals, int totalNodes);

std::vector<int> aStar(std::vector<std::pair<int, int>> adjacent[], int startNode, const std::vector<int>& goals, int totalNodes, int dimension);
#endif // !SEARCHTREE_H