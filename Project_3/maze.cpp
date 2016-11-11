#include "grid.h"
#include <string>
#include <cctype>
#include <iostream>
#include <cassert>
using namespace std;
bool isPathWellFormed(string path);
int traverseSegment(int r, int c, char dir, int maxSteps);
int traversePath(int sr, int sc, int er, int ec, string path, int& nsteps);
int traverseSegmentEast(int r, int c);

int main()
{
	setSize(3,4);
	setWall(1,4);
	setWall(2,2);
	if (!isWall(3,2))
	setWall(3,2);
	draw(3,1, 3,4);
	int numSteps;
	assert(isPathWellFormed("2N1e01E0n2e1e") == true);
	assert(isPathWellFormed("4se") == false);
	assert(isPathWellFormed("3s2") == false);
	assert(isPathWellFormed("3s 2n") == false);
	assert(isPathWellFormed("2w+3n") == false);
	assert(isPathWellFormed("") == true);
	assert(isPathWellFormed("144N") == false);
	assert(isPathWellFormed("2N1f") == false);

	assert(traverseSegment(1,1,'e',2) == 2);
	assert(traverseSegment(3,1,'n',2) == 2);
	assert(traverseSegment(2,4,'s',1) == 1);
	assert(traverseSegment(3,4,'w',1) == 1);
	assert(traverseSegment(3,1,'n',1) == 1);
	assert(traverseSegment(2,4,'w',3) == 1);
	assert(traverseSegment(0,0,'n',1) == -1);
	assert(traverseSegment(3,2,'s',1) == -1);
	assert(traverseSegment(1,1,'q',1) == -1);
	assert(traverseSegment(1,1,'s',-3) == -1);

	assert(traversePath(3,1,3,4,"2n2E2S1e", numSteps) == 0);
	cout << numSteps << endl;
	assert(traversePath(3,1,3,4,"2n2E2S", numSteps) == 1);
	cout << numSteps << endl;
	assert(traversePath(3,1,3,4,"32q", numSteps) == 3);
	cout << numSteps << endl;
	assert(traversePath(3,1,3,4,"2n2E3w", numSteps) == 2);
	cout << numSteps << endl;
	assert(traversePath(0,0,3,4,"2n2E2S1e", numSteps) == 3);
	cout << numSteps << endl;
	assert(traversePath(3,1,1,4,"2n2E2S1e", numSteps) == 3);
	cout << numSteps << endl;
	cout << "yes" << endl;
}

bool isPathWellFormed(string path)
{
	int k = 0;
	int i = 0;
	while (k != path.size())
	{
		i = 0;
		if(!isdigit(path[k]))	//The character should be a number, so return false if not.
			return false;
		while(isdigit(path[k]) && i < 2)	 //Go through all numbers until it hits a character.
		{
			k++;
			i++;
			if(k >= path.size())	//If ends on a number, ensures that program does not
				return false;		//try to go out of the string.
		}
		switch(path[k])	//Make sure character is valid.
		{
			case 'n':
			case 'N':
				k++;
				break;
			case 'e':
			case 'E':
				k++;
				break;
			case 's':
			case 'S':
				k++;
				break;
			case 'w':
			case 'W':
				k++;
				break;
			default:
				return false;
		}
	}
	return true;
}

int traverseSegment(int r, int c, char dir, int maxSteps)
{
	if(r > getRows() || c > getCols())	//Check to ensure that the variables given are usable and that it does not start at a wall.
		return -1;
	if(r <= 0 || c <= 0)
		return -1;
	if(isWall(r,c))
		return -1;
	if(maxSteps < 0)
		return -1;

	bool proceed = true;
	int currentSteps = 0;
	
	while(currentSteps < maxSteps && proceed)
	{
		switch(dir)	//Check the direction, then find up to how many steps can be taken.
		{
			case 'n':
			case 'N':	
				if(r > 1 && c > 0 && r <= getRows() && c <= getCols())
				{
					if(!isWall(r - 1,c))
					{
						r -= 1;
						currentSteps++;
					}
					else
						proceed = false;
				}
				else
					proceed = false;
				break;
			case 's':
			case 'S':
				if(r > 0 && c > 0 && r <= getRows() - 1 && c <= getCols())
				{
					if(!isWall(r + 1,c))
					{
						r += 1;
						currentSteps++;
					}
					else
						proceed = false;
				}
				else
					proceed = false;
				break;
			case 'w':
			case 'W':
				if(r > 0 && c > 1 && r <= getRows() && c <= getCols())
				{
					if(!isWall(r,c - 1))
					{
						c -= 1;
						currentSteps++;
					}
					else
						proceed = false;
				}
				else
					proceed = false;
				break;
			case 'e':
			case 'E':
				if(r > 0 && c > 0 && r <= getRows() && c <= getCols() - 1)
				{
					if(!isWall(r,c + 1))
					{
						c += 1;
						currentSteps++;
					}
					else
						proceed = false;
				}
				else
					proceed = false;
				break;
			default:
				return -1;
		}
	}
	return currentSteps;
}

int traversePath(int sr, int sc, int er, int ec, string path, int& nsteps)
{
	int k = 0;
	string number = "";
	int steps = 0;
	int currentRow = sr;
	int currentCol = sc;
	int segment = 0;
	nsteps = 0;

	if(sr > getRows() || sc > getCols())	//Check to ensure that the variables given are usable and that it does not start or end at a wall.
		return 3;
	if(sr <= 0 || sc <= 0)
		return 3;
	if(er > getRows() || ec > getCols())
		return 3;
	if(er <= 0 || ec <= 0)
		return 3;
	if(isWall(sr,sc))	
		return 3;
	if(isWall(er,ec))
		return 3;
	if(!isPathWellFormed(path))
		return 3;

	while (k != path.size())
	{
		number = "";
		steps = 0;

		while(isdigit(path[k]))
		{
			number += path[k];	//Add digit into string variable number.
			k++;
		}
		for(int i = 0; i != number.size(); i++)	//Turn the string number into an integer variable steps.
		{
			steps *= 10;
			steps += number[i] - '0';
		}
		segment = traverseSegment(currentRow,currentCol, path[k], steps); //Find how many steps are possible and add to nsteps.
		nsteps += segment;
		if(segment != steps) //If the segment does not equal steps, the path cannot be completed, so return 2.
			return 2;
		switch(path[k])	//Add or subtract from currentRow or currentCol based on direction moved to simulate the movement.
		{
			case 'n':
			case 'N':
				currentRow -= segment;
				break;
			case 'e':
			case 'E':
				currentCol += segment;
				break;
			case 's':
			case 'S':
				currentRow += segment;
				break;
			case 'w':
			case 'W':
				currentCol -= segment;
				break;
		}
		k++;
	}
	if(currentRow == er && currentCol == ec)	//Return 0 if it ends at (er,ec) and 1 if not.
		return 0;
	else
		return 1;
}