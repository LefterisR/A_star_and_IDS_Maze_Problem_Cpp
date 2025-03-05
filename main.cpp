#include <iostream>
#include <vector>
#include "graph.h"
#include "spacestate.h"
#include <queue>
#include "SearchTree.h"
#include <Windows.h>
#include <string>
//@Author Lefteris Rizos
const int DEFAULT_COLOR = 7;

using namespace std;
/*
*Function used to check if an input is a number or a char
* Vital to avoid crashes during array and vector memory allocations
*/
bool isDigit(string& input)
{
    for (char ASCII_VALUE : input) {
        
        if (!(ASCII_VALUE >= 48 && ASCII_VALUE <= 57)) {
            return false;
        }
    }

    return true;
}

/*
initialiseValues takes all the arguments as references
so they can be used in main
*/

void initialiseValues(int &dimension,int &xDen, int &tDen)
{
	float x, t;                                                      //To save the PERCENTAGES of X and Y
    string input;
    bool inputError = false;
    int convertedValue = 0;

	cout << ">Please enter the n dimension of the board." << endl<<">n has to be an even positive number:"; 

    do {
        cin >> input;

        inputError = isDigit(input);
        
        if (!inputError) 
        {
            cout << ">>Invalid input! Please type only numbers:";
        }
        
        if (inputError)
        {
            convertedValue = stoi(input);
            if (convertedValue % 2 != 0 || convertedValue<=2)                                                   //Inside that block dimension is definately an number
            {                                                                                                   //Now, we check if it is in range and an even number
                inputError = false;
                if (convertedValue <= 2) { cout << ">>The dimension of the table must be greater than 2." << endl; }
                cout << ">>The dimension of the table must be an even number! Give another imput:";
                
            }
        }
    } while (!inputError);

    dimension = convertedValue;

    cout << ">The dimension was set to: " << dimension << endl;

	cout << ">Please enter the desired percentage of X squares on maze:";
	
    do
    {
        cin >> x;
        if (x > 100) cout << ">>X cannot have a value greater than 100%.Type again:";

    } while (x > 100);
    float temp = x;
	
    xDen = static_cast<int>(dimension * dimension *(x / 100));                   //The program takes the density percetange then type casting it into an inter number of space squares

	
    if (temp == 100)
    {
        cout << ">Since the density of the X is 100%,the density of the T can only be 0." << endl;
        t = 0;
    }
    else {

        cout << ">Please enter the desired percentage o T squares on maze:";
        do {
        cin >> t;
        if (t > 100) cout << ">>T cannot have a value greater than 100%.Type again:";
        } while (t > 100);
    }
	tDen = static_cast<int>(dimension * dimension *(t / 100));                    //The program takes the density percetange then type casting it into an inter number of space squares

    cout << "________________________end_of_init________________________" << endl;
}   

bool checkForPathNode(int node,const vector<int> &path)
{
   vector<int>::const_iterator it;
   it = find(path.begin(), path.end(), node);
   if (it != path.end()) return true;
    return false;
}

/*
Function to print the path from start to goal
*/
void diplayPathToSpace(const vector <int> path,int dimension,int startNode,char** saveStateSpace,int colourCode)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                                                                         
    if (!path.empty()) {                                        
        cout << "Path found: ";                                              //First print the path as simple line of numbers
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;

        int currentNode = 0;
                                                                             //Second print the space state with interfering chars in the position of path nodes
        for (int row = 0; row < dimension; row++)
        {
            for (int col = 0; col < dimension; col++)
            {
                if (checkForPathNode(currentNode, path)  && currentNode != startNode && saveStateSpace[row][col] != 'E')    //If the current node/square is a path node and we arent at the robot place and exit
                {
                    SetConsoleTextAttribute(hConsole, colourCode);           //Change the colour for a more clear path reprentasion
                    if (saveStateSpace[row][col] == '#')                     //Print 1 for simpe squares
                        cout << "1 ";
                    else if (saveStateSpace[row][col] == 'T')                //And 'T' in different colour for T that are a part of path
                        cout << "T ";
                    SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);        //Switch to default white colour
                }
                else
                {
                    cout << saveStateSpace[row][col] << " ";                 //If the current square is not a part of the path continue printing the stace space

                }
                currentNode++;                                               //Move to the next node
            }
            cout << endl;
        }
        SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);                    //After the printing of the state space + the path ensure that consol displays in the default white colour


    }
    else {                                                                   //If the path is empty, the algorithm did not found a solution
        cout << "No path found from " << startNode << " to any goal"<<endl;
    }

}



int main()
{
    
	int dimension = 0;
	int xDensity = 0, tDensity =0;

    cout << "* * * * * * * * * * * * Start Program * * * * * * * * * * * *" << endl;

	initialiseValues(dimension,xDensity,tDensity);                                                            //Initialise values

	int  totalNodes = dimension*dimension;                                                                    //The total nodes are equal to the area our state Space, if the smallest area unit is a square inside state Space
   
	vector <pair<int, int>>* board = new vector<pair<int,int>> [totalNodes];                                  //Dynamically allocate the space for our graph.
	
	stateSpace space(dimension, xDensity, tDensity);                                                          //Create a space state object

	space.spaceStateInit();

	space.spaceStatePlacements();
	
	space.displaySpaceState();

	char** saveStateSpace = space.getSpace();                                                            //save the space state in main

	Graph graph(dimension, totalNodes);                                                                  //Create a graph object
	
	graph.spaceToGraph(board,space);                                                                     //Translate the space to a graph

	//graph.displayGraph(board);

    int startNode = graph.getRobotNode();                                                                //Save the starting node 
   cout << "THIS IS THE ROBOT NODE:" << startNode<<endl;
    
   //**********************************************
   
   vector<int> goalNodes = {0,totalNodes-1};                                                             //Create a goal vector to pass to the Search Algorithms
  

   cout << endl << "______________________Iterative_Deepening_Search______________________" << endl; 
   
   
   const vector<int>& pathIDS = ids(board, startNode, goalNodes, totalNodes);
  
   diplayPathToSpace(pathIDS,dimension,startNode,saveStateSpace,FOREGROUND_BLUE);
   
   cout << endl << "_______________________A*_Manhattan_Heuristic________________________" << endl;
   
   vector <int> pathAstar = aStar(board, startNode, goalNodes, totalNodes, dimension);
   
  diplayPathToSpace(pathAstar, dimension, startNode, saveStateSpace, FOREGROUND_GREEN);

  delete[] board;                                                                                        //De allocate the graph memory                    
  cout <<endl<< ">Graph memory de-allocated..."<<endl;
  space.deleteStateSpace();

  cout <<endl <<"___________________________End_Of_Program____________________________" << endl;
  
  system("PAUSE");
   return 0;
}