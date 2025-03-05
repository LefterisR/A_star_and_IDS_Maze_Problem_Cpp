#include <iostream>
#include <vector>
#include <utility>
#include "graph.h" 
#include "spacestate.h"

using namespace std;
//@Author Lefteris Rizos
//UNDIRECTED GRAPH

Graph::Graph(int dimension,int totalNodes)
{   
    this->dimension = dimension;
    rows = dimension;                                                //Since the state space is a square rows = columns
    columns = dimension;
    this->totalNodes = totalNodes;                                   //Vital info for graph class, defines the nodes of the graph, wrong input will result to program failure
}

/*Add edges on the graph given 2 nodes it will connect node 1 with 2 and vice verca with a cost of int cost*/

void Graph::addEdge(vector<pair <int, int> > adjacent[], int u, int v, int cost)
{   
    //Each node will be saved to a vector of pairs.
    //The vector/node [x] will have all of its connections with other nodes and accompanied by the corresponing costs, saved in a pair. 
	
    adjacent[u].push_back(make_pair(v, cost));                           //node u connects to v with cost of cost
	adjacent[v].push_back(make_pair(u, cost));                          //at the same time the vector of the same u records this connection in a pair since the graph is undirected
}

/* Simple display function, the outer loop selects with vector/node will pressent its data 
and the inner prints every pair*/

void Graph::displayGraph(vector<pair <int, int>> a[])
{
    int v, cost;
    vector<pair <int, int>>::iterator itr;
    for (int u = 0; u < totalNodes; u++)
    {
        cout << "Node " << u << " connects to " << endl;
        for (itr = a[u].begin(); itr != a[u].end(); itr++)
        {
            v = itr->first;                                          //connected nodes
            cost = itr->second;                                      //connection cost
            cout << "Node " << v << " with a cost of " << cost << endl;

        }
        cout << endl;
    }
}

/*
spaceToGraph is responsible for translating the space to a graph.
The main philosophy is processing the space from left to right
performing connection with the right node and the upper node.
ALWAYS checking if the afformentioned node exists, what is there 
and if we are inside bounds.
Since the addEdge() is designed to include the creation of the opposite connection
by making the right and upper connection both the left and the lower connection are created
*/

//Right is defined in stateSpace coordinates as (row,column+1) and in graph nodes: currentNodeNum+1 
//Up is defined in stateSpace coordinates as (row-1,column) and in graph nodes: currentNodeNum-dimension

void Graph::spaceToGraph(vector <pair <int, int>> a[], stateSpace s)
{                                                                    
    int row = 0, nodeNumber = 0;                                     //Each square in State Space is a Node in the graph, the nodeNumber keeps a track of them during placement
    int cost = 0;                                                    //Starting with nodeNumber 0, top left sqaure and ending with nodeNumber dimension*dimension-1, bottom left square

    char** space = s.getSpace();                                     //Accessing the StatesSpace, see "statespace.h"

    do {
                                                                     //The first row does not have any "upper" nodes, no connection with addEdge() needed.
        if (row == 0)
        {
            for (int column = 0; column < dimension; column++)       //Read the the line of the space state from left to right
            {
                if (space[row][column] == 'X') nodeNumber++;         //If I am X move to the next node
                 else 
                 {

                    if (column != dimension - 1 )                    //We are not at the end of the row. Checking to avoid going out of bound in the space 
                    { 
                      if (space[row][column+1] == 'X') nodeNumber++; //If the next node is X move to the next node :! note that the previous 'if' warranties that space will not go out of bounds to check
                      else
                      {                                              //If the next node is not an X we perform the appropriate checks to define the connection cost 
                         if (space[row][column] == 'T') cost = 2;    
                         else if (space[row][column + 1] == 'T') cost = 2;
                         else cost = 1;
                         addEdge(a, nodeNumber, nodeNumber + 1, cost); //Node i (for example 0) would be connected to node i+1  (1) and vice versa
                         nodeNumber++;
                      }

                    }
                    else nodeNumber++;                               //If we are at the end of the row AND at the row 0, there is no need to perfome any connections and we skip this node


                 }
            }
            row++;                                                   //We have read the first line of the space (column now = to dimension -1 ), move to next.
        }
        else                                                         //Now all we have are the Rows>0 and we have to perform a connection with the upper node as well.
        {
            for (int column = 0; column < dimension; column++)       //Again read the line
            {    
               if (space[row][column] == 'R') robotNode = nodeNumber;       //By definition Robot node could not be in the zero row.

               if (space[row][column] == 'X') nodeNumber++;                 //If I am X move to the next node
               else {
                    if (column != dimension - 1)                            //We are not at the end of the row
                    {
                      if (space[row][column] == 'T') cost = 2;              //If I am T change the cost
                      else if (space[row][column + 1] == 'T') cost = 2;     //If I am not T check the right square
                      else cost = 1;                                      
                            
                      if (space[row][column + 1] != 'X') addEdge(a, nodeNumber, nodeNumber + 1, cost);  //We have already checked if I am X (line 104) , time to check the right node
                            
                      cost = 1;                                             //Set the cost = 1, Here we performs the connection with the upper nodes.
                           
                      if (space[row][column] == 'T')                        
                      {
                       cost = 2;
                      }
                      else if (space[row][column] != 'T') 
                      {
                      if (space[row - 1][column] == 'T') cost = 2;
                      }
                      else cost = 1;

                      if (space[row - 1][column] != 'X') addEdge(a, nodeNumber, nodeNumber - dimension, cost); //check if the upper node is not X
                      nodeNumber++;

                    }
                    else                                                    //Here we are at rows > 0 and at the end of the line. Only need to perform connection with the upper nodes
                    {
                        if (space[row][column] == 'T')
                        {
                            cost = 2;
                        }
                        else if (space[row][column] != 'T')
                        {
                            if (space[row - 1][column] == 'T') cost = 2;
                        }
                        else cost = 1;
                        if (space[row - 1][column] != 'X') addEdge(a, nodeNumber, nodeNumber - dimension, cost);
                        nodeNumber++;

                    }
                }
            }
            
            row++;                                                          //Move to the next row

        }

    } while (nodeNumber < dimension * dimension);

}


