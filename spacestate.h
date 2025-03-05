#pragma once
#ifndef STATESPACE_H
#define STATESPACE_H

/*Space State class 
*Creates the Space State, Places randomly the elements
*Prints the space
* the Algoritms DOES NOT run upon Space State objects
*/
//@Author Lefteris Rizos
class stateSpace
{
private:
	int dimension;
	int numofX;
	int numofT;
	char** space;
public:

	stateSpace(int dimension, int numofX, int numofT);
	
	void deleteStateSpace();

	void spaceStateInit();

	void spaceStatePlacements();

	void displaySpaceState();

	char** getSpace();
};

#endif