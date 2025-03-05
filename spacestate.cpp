#include "spacestate.h"
#include <iostream>
#include <random>
#include <map>
//@Author Lefteris Rizos
stateSpace::stateSpace(int dimension, int numofX, int numofT)
{
	this->dimension = dimension;                                       //Save the dimension of the square
	this->numofX = numofX;											   //The number of X which must be placed in the space 
	this->numofT = numofT;										       //The number of T which must be placed in the space 	

	                                                                   //Dynamically allocate memory for the space array
	space = new char* [dimension];
	for (int i = 0; i < dimension; i++)
	{
		space[i] = new char[dimension];
	}
}

void stateSpace::deleteStateSpace()									   //Function to deallocate the memory used by space array			
{
	for (int i = 0; i < dimension; i++)
	{
		delete[] space[i];

	}

	delete[] space;

	std::cout << ">State Space memory de-allocated...\n";
}

void stateSpace::spaceStateInit()                                      //In this function, # (symbol for an empty square with traverse cost one) are been placed.
{
	for (int row = 0; row < dimension; row++)
	{
		for (int col = 0; col < dimension; col++)
		{
			space[row][col] = '#';                                     //Placed in each and every position inside the array.

		}

	}

}

void stateSpace::spaceStatePlacements()
{
	
	std::random_device rd;                                             //uniformly-distributed integer random number generator that produces non-deterministic random numbers used as seed
	std::mt19937 gen(rd());                                            //class / efficient pseudo-random number generator passind random_device rd as seed

	
	std::uniform_int_distribution<> dis(0, dimension - 1);             //Setting the uniform destribution 0 to dimension-1, which is the valid domain of both x & y coord in spaceState
	std::uniform_int_distribution<> robot(0, 3);                       //Keys 0,1,2 and three each connected to one of the 4 valid starting positions

	int	placed = 0;                                                    //Keeps track of the number of placed X and T inside the SpaceState
	int x = 0, y = 0;
	                                                                   //Placing the Exits in the fixed positions top left & top right square of the space state
	space[0][0] = 'E';
	
	space[dimension - 1][dimension - 1] = 'E';
	int d = dimension - 1;
	                                                                   //Initialise the map of the Robot Positions ,each key (0-3) defines one possible position
	std::map<int, std::pair<int, int>> robotPos =
	{
		{0,{d / 2,d / 2} },
		{1,{d / 2 + 1,d / 2} },
		{2,{d / 2,d / 2 + 1} },
		{3,{d / 2 + 1,d / 2 + 1} }

	};
	
	int wantedPos = robot(gen);                                        //Get the random key

	std::pair<int, int> position;

	position = robotPos[wantedPos];                                    //Save the x,y of the random starting pos
	
	std::cout <<std::endl<<"Robot Position x:" << position.first << " y:" << position.second << std::endl;
	
	space[position.first][position.second] = 'R';                      //Place the Robot on the random pos
	
	if (numofX == dimension) { numofX = numofX - 3; }                  //Overide the density of X to exclude the pre occupied posision by 2E and 1R 
																	   //Still a high X & T density will slow down the program as it will linearly tries to find available pos for placement
	while (placed < numofX)                                            //Runs till the wanted number of X have been reached
	{
		x = dis(gen);                                                  // random x & y of the X's pos
		y = dis(gen);
		//std::cout << "Test x: " << x << " y: " << y << std::endl;
		if (space[x][y] != 'X' && space[x][y] != 'E' && space[x][y]!='R')    //Checking if the randomly selected pos is available (empty)
		{
			space[x][y] = 'X';                                               //If it is, place X and increment the placed
			placed++;

		}


	} 
	x = 0, y = 0;

	placed = 0;                                                        //Set placed to 0 to keep track of placed T
	while (placed < numofT) {
		x = dis(gen);
		y = dis(gen);
		//std::cout << "Test x: " << x << " y: " << y << std::endl;
		if (space[x][y] != 'X' && space[x][y] != 'E' && space[x][y] != 'T' && space[x][y] != 'R')
		{
			space[x][y] = 'T';
			placed++;

		}


	} 


	


}

/*Simple function to print the Space State*/
void stateSpace::displaySpaceState()
{
	for (int row = 0; row < dimension; row++)
	{
		for (int col = 0; col < dimension; col++)
		{
			std::cout << space[row][col] << " ";

		}

		std::cout << std::endl;
	}

}
//Returns the space
char** stateSpace::getSpace()
{
	return space;
}

