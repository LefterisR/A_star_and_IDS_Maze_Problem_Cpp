#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "SearchTree.h"
#include <iterator>
#include <utility>
//@Author Lefteris Rizos
using namespace std;

/*IDS Algorithm*/
vector<int> ids(vector <pair<int, int>> adjacent[], int start, const std::vector<int>& goals, int totalNodes)
{
	int createdNodeCounter = 1;
	
	for (int depth = 1; depth<totalNodes; depth++)                                            //Incrementing the depth, a good limit is till reach the totalNodes number 
	{                                                                                         //in the imaginery case that nodes are "following" each other in a line and the goal is at the end of it
		vector<int> explored(totalNodes, false);
		
		vector <pair<int, int>>  parent(totalNodes, make_pair(-1, 0));                     
		
		stack<Node> frontier;                                                                //Utilize as a frontier a stack
		frontier.push(Node(start, 0, 0));                                                    //Everything is initialized again after a depth incrementation since a new  
		                                                                                     //search tree is being created for all of different depths

		while (!frontier.empty())                                                            //Searching while the frontier is not empty, if it empties increase the depth
		{
			Node current = frontier.top();                                                   //Save the top Node of the stack
			frontier.pop();

			int currentVertex = current.getVertex();
			int currentCost = current.getCost();
			//cout << currentCost << endl;
			int currentDepth = current.getDepth();

			vector<int>::const_iterator it = find(goals.begin(), goals.end(), currentVertex);              //The reconstruction of the goal path follows the same phylosophy as the UCS one
			if (it != goals.end())
			{
				vector<int> path;
				int vertex = currentVertex;
				int totalPathCost = 0;
				
				while (vertex != start)
				{
					path.push_back(vertex);
					
					vertex = parent[vertex].first;
					totalPathCost += parent[vertex].second;

					
					
					
				}
				path.push_back(start);
				reverse(path.begin(), path.end());

				cout << endl << endl << "The total cost from the start to the goal is :" << totalPathCost+1<< endl;
				cout << "A path from the start to a goal have been found." << endl << "The depth in the search tree from the root/start to the goal is equal to " << currentDepth << endl;
				cout << createdNodeCounter << " nodes have been created by IDS in order to find the goal." << endl;
				
				
				
				return path;
			}

			explored[currentVertex] = true;                                               //Marks the path to the current vertex as visited
			                                                                             //if the current depth is less the the allowed depth proceed to expansion
			if (currentDepth < depth)
			{
				for (const auto& neighbor : adjacent[currentVertex])                    //The current vertex is expanding to all of its neighbors
				{
					int neighborVertex = neighbor.first;
					if (!explored[neighborVertex])
					{
						frontier.push(Node(neighborVertex, currentCost + neighbor.second, currentDepth + 1));     //Push each node to the stack accounting for their new costs and depth
						parent[neighborVertex] = make_pair(currentVertex, neighbor.second);
						createdNodeCounter++;
					}
				}
			}
			

		}

	}
	                                                                                     //In case of reaching the depth limit without finding the goal, terminate with failure
	return vector<int>();                                                                //return an empty path
}
	

/*
Heuristic function used by A star
Manhattan implementation
*/

int heuristic(int vertex, int dimension, int goal)
{
	int x = vertex % dimension;                            //Calculate the coordinates of each vertex inside the state space
	int y = vertex / dimension;                            

	int xGoal = 0;                                         //Initialise goal coordinates
	int yGoal = 0;
	//goal = 2;
	if (goal == 0)                                         //If we are searching for the goal 0 update the Goal(x,y)
	{
		// Goal A coordinates
		xGoal = 0;
		yGoal = 0;
	}
	else if (goal == 1)                                    //If we are searching for the goal 0 update the Goal(x,y)
	{
		// Goal B coordinates
		xGoal = dimension - 1;
		yGoal = dimension - 1;
	}

	int dx = abs(x - xGoal);                               //Calculate the horizontal distance from x to goalx
	int dy = abs(y - yGoal);                               //Calculate the vertical distance from y to goaly

	return 1 * (dx + dy);                                 //Add the distances whilist giving to each step the arbitrary cost of 1
}

/*Astar Algorithm*/
vector<int> aStar(vector<pair<int, int>> adjacent[], int startNode,const vector<int>& goals, int totalNodes, int dimension)
{
	
		priority_queue<Node, vector<Node>, greater<Node>> frontier;
		
		vector<int> gCost(totalNodes, INT_MAX);                                         //f(node) = g(node) + heuristic
		vector<int> fCost(totalNodes, INT_MAX);                                         //F and G cost keep track of the cost to traverse to a specific vertex. F is the cost after the addition of h
		                                                                                //We fill each value of all vector with the maximum possible integer value, to use later in cost comparison
		vector <pair<int, int>>  parent(totalNodes, make_pair(-1, 0));

		gCost[startNode] = 0;                                                          //We initialize the g=0 for the start node
		fCost[startNode] = heuristic(startNode, dimension, 0);                         //Arbitary, selecting the manhattan distance for the goal0 for initialization

		frontier.push(Node(startNode, fCost[startNode], 0));                           //We create and push the starting Node in the search tree note that the cost is f=h+g however g here is 0
		int createdNodeCounter = 1;
		while (!frontier.empty())                                                      
		{
			Node current = frontier.top();
			frontier.pop();

			if (find(goals.begin(), goals.end(), current.getVertex()) != goals.end())              //The reconstruction of the goal path follows the same principles as in UCS
			{
				
				vector<int> path;
				int currentVertex = current.getVertex();
				int currentDepth = current.getDepth();
				int currentCost = current.getCost();
				int totalPathCost = 0;
				while (currentVertex != startNode)
				{
					path.push_back(currentVertex);
					currentVertex = parent[currentVertex].first;
					totalPathCost += parent[currentVertex].second;
					//cout << "Debug costA* : " << totalPathCost << endl;
				}
				path.push_back(startNode);

				reverse(path.begin(), path.end());
				totalPathCost += 1;
				cout << endl << endl << "The total cost from the start to the goal is :" << currentCost  << endl;
				cout << "A path from the start to a goal have been found." << endl << "The depth in the search tree from the root/start to the goal is equal to " << currentDepth << endl;
				cout << createdNodeCounter << " nodes have been created by Astar in order to find the goal." << endl;

				return path;
			}

			

			for (const auto& neighbor : adjacent[current.getVertex()])                                            //In case that the top element of the frontier is not the goal
			{                                                                                                     //We move to expansion
				int neighborVertex = neighbor.first;
				int edgeCost = neighbor.second;
				int tentativeGScore = gCost[current.getVertex()] + edgeCost;                                      //Here the ternary cost marks costs to visit a specific neighbor node.
				
				int distanceFromGoal0 = 0, distanceFromGoal1=0;
				int manhattanDistance = 0;

				if (tentativeGScore < gCost[neighborVertex])                                                      //If a node is visited for the first time INT_MAX comes into play
				{                                                                                                 //And the gCost, the cost to traverse that node is always smaller
					gCost[neighborVertex] = tentativeGScore;                                                      //If a ternary cost exist we chech if it smaller than the previous gCost
					distanceFromGoal0 = heuristic(neighborVertex, dimension, 0);                                  //If it is, it means we have found a shortes path to that neighboor node
					distanceFromGoal1 = heuristic(neighborVertex, dimension, 1);                                  //Since the alg is searching simultaneously for both goals, we calculate both manhattan distances 
					
					if (distanceFromGoal0 > distanceFromGoal1) manhattanDistance = distanceFromGoal1;             //After a check, of course proceed with the lower manhattan distance, in other words, search for the nearest goal
					else manhattanDistance = distanceFromGoal0;

					fCost[neighborVertex] = tentativeGScore + manhattanDistance;                                  //Calculate the new fCost, by adding the new tentative cost + the manhattan distance
					
					frontier.push(Node(neighborVertex, fCost[neighborVertex], current.getDepth()+1));             //Add that vertex to the search tree
					createdNodeCounter++;
					parent[neighborVertex] = make_pair(current.getVertex(),neighbor.second);                      //Always mark the paths
				}
			}
		}

		
		return vector<int>();                              //If the frontier is empty, we have searched every possible path without success. Return an empty path and end with Failure
	
}


