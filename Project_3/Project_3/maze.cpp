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
void makemaze();
void testone(int n);
int main()
{
    cout << "Enter test number: ";
    int n;
    cin >> n;
    testone(n);
    cout << "Passed!" << endl;
}
void testone(int n)
{
	switch (n)
	{
			         default: {
	    cout << "Bad argument" << endl;
			} break; case  1: {
            assert(isPathWellFormed(""));
                        } break; case  2: {
            assert(!isPathWellFormed("x"));
                        } break; case  3: {
            assert(!isPathWellFormed("3"));
                        } break; case  4: {
            assert(!isPathWellFormed("N"));
                        } break; case  5: {
            assert(!isPathWellFormed("1x"));
                        } break; case  6: {
            assert(!isPathWellFormed("12"));
                        } break; case  7: {
            assert(!isPathWellFormed("12@"));
                        } break; case  8: {
            assert(isPathWellFormed("03E"));
                        } break; case  9: {
            assert(!isPathWellFormed("003E"));
                        } break; case 10: {
            assert(!isPathWellFormed("1n#"));
                        } break; case 11: {
            assert(isPathWellFormed("2e"));
                        } break; case 12: {
            assert(isPathWellFormed("10N"));
                        } break; case 13: {
            assert(isPathWellFormed("98n"));
                        } break; case 14: {
            assert(isPathWellFormed("1S2W"));
                        } break; case 15: {
            assert(isPathWellFormed("12s3w"));
                        } break; case 16: {
            assert(isPathWellFormed("1n12e"));
                        } break; case 17: {
            assert(isPathWellFormed("12n12e"));
                        } break; case 18: {
            assert(!isPathWellFormed("1n12e1"));
                        } break; case 19: {
            assert(!isPathWellFormed("12n12n@"));
                        } break; case 20: {
            assert(!isPathWellFormed("12n12n1@"));
                        } break; case 21: {
            assert(!isPathWellFormed("12n12e1@s"));
			} break; case 22: {
            makemaze();
            assert(traverseSegment(0,4,'S',2) == -1);
                        } break; case 23: {
            makemaze();
            assert(traverseSegment(6,4,'N',2) == -1);
                        } break; case 24: {
            makemaze();
            assert(traverseSegment(3,0,'E',2) == -1);
                        } break; case 25: {
            makemaze();
            assert(traverseSegment(3,13,'W',2) == -1);
                        } break; case 26: {
            makemaze();
            assert(traverseSegment(4,3,'E',2) == -1);
                        } break; case 27: {
            makemaze();
            assert(traverseSegment(3,4,'E',-1) <= 0);
                        } break; case 28: {
            makemaze();
            assert(traverseSegment(3,4,'E',0) == 0);
                        } break; case 29: {
            makemaze();
            assert(traverseSegment(3,4,'e',2) == 2);
                        } break; case 30: {
            makemaze();
            assert(traverseSegment(1,3,'s',2) == 2);
                        } break; case 31: {
            makemaze();
            assert(traverseSegment(1,3,'w',2) == 2);
                        } break; case 32: {
            makemaze();
            assert(traverseSegment(3,7,'n',0) == 0);
                        } break; case 33: {
            makemaze();
            assert(traverseSegment(3,7,'E',2) == 2);
                        } break; case 34: {
            makemaze();
            assert(traverseSegment(3,6,'S',2) == 2);
                        } break; case 35: {
            makemaze();
            assert(traverseSegment(3,6,'N',2) == 2);
                        } break; case 36: {
            makemaze();
            assert(traverseSegment(2,3,'S',3) == 1);
                        } break; case 37: {
            makemaze();
            assert(traverseSegment(2,8,'W',3) == 0);
                        } break; case 38: {
            makemaze();
            assert(traverseSegment(4,7,'N',2) == 1);
                        } break; case 39: {
            makemaze();
            assert(traverseSegment(2,3,'E',8) == 3);
                        } break; case 40: {
            makemaze();
            assert(traverseSegment(4,5,'W',8) == 1);
                        } break; case 41: {
            makemaze();
            assert(traverseSegment(3,4,'W',4) == 3);
                        } break; case 42: {
            makemaze();
            assert(traverseSegment(3,4,'e',10) == 8);
                        } break; case 43: {
            makemaze();
            assert(traverseSegment(3,4,'S',3) == 2);
                        } break; case 44: {
            makemaze();
            assert(traverseSegment(3,4,'N',4) == 2);
	    		} break; case 45: {
            makemaze(); int nsteps = 999;
            assert(traversePath(0,4,1,4,"1s",nsteps) == 3  &&  nsteps == 999);
                        } break; case 46: {
            makemaze(); int nsteps = 999;
            assert(traversePath(1,13,1,12,"1w",nsteps) == 3  &&  nsteps == 999);
                        } break; case 47: {
            makemaze(); int nsteps = 999;
            assert(traversePath(5,2,6,2,"1s",nsteps) == 3  &&  nsteps == 999);
                        } break; case 48: {
            makemaze(); int nsteps = 999;
            assert(traversePath(2,7,2,6,"1w",nsteps) == 3  &&  nsteps == 999);
                        } break; case 49: {
            makemaze(); int nsteps = 999;
            assert(traversePath(2,6,2,7,"1E",nsteps) == 3  &&  nsteps == 999);
                        } break; case 50: {
            makemaze(); int nsteps = 999;
            assert(traversePath(3,4,2,4,"1?",nsteps) == 3  &&  nsteps == 999);
                        } break; case 51: {
            makemaze(); int nsteps = 999;
            assert(traversePath(4,7,1,7,"3N1EW",nsteps) == 3  &&  nsteps == 999);
                        } break; case 52: {
            makemaze(); int nsteps = 999;
            assert(traversePath(4,7,1,7,"3n",nsteps) == 2  &&  nsteps == 1);
                        } break; case 53: {
            makemaze(); int nsteps = 999;
            assert(traversePath(4,6,2,8,"2n2e",nsteps) == 2  &&  nsteps == 2);
                        } break; case 54: {
            makemaze(); int nsteps = 999;
            assert(traversePath(4,5,2,8,"2n3e",nsteps) == 2  &&  nsteps == 3);
                        } break; case 55: {
            makemaze(); int nsteps = 999;
            assert(traversePath(4,5,5,4,"2s",nsteps) == 2  &&  nsteps == 1);
                        } break; case 56: {
            makemaze(); int nsteps = 999;
            assert(traversePath(3,11,4,5,"2e1s3w",nsteps) == 2  &&  nsteps == 1);
                        } break; case 57: {
            makemaze(); int nsteps = 999;
            assert(traversePath(5,11,4,5,"2N2E1S3W",nsteps) == 2  &&  nsteps == 3);
                        } break; case 58: {
            makemaze(); int nsteps = 999;
            assert(traversePath(5,3,5,4,"",nsteps) == 1  &&  nsteps == 0);
                        } break; case 59: {
            makemaze(); int nsteps = 999;
            assert(traversePath(5,3,5,3,"",nsteps) == 0  &&  nsteps == 0);
                        } break; case 60: {
            makemaze(); int nsteps = 999;
            assert(traversePath(5,3,5,3,"1E",nsteps) == 1  &&  nsteps == 1);
                        } break; case 61: {
            makemaze(); int nsteps = 999;
            assert(traversePath(2,1,2,4,"3E",nsteps) == 0  &&  nsteps == 3);
                        } break; case 62: {
            makemaze(); int nsteps = 999;
            assert(traversePath(2,1,2,3,"3E",nsteps) == 1  &&  nsteps == 3);
                        } break; case 63: {
            makemaze(); int nsteps = 999;
            assert(traversePath(2,1,2,5,"3E",nsteps) == 1  &&  nsteps == 3);
                        } break; case 64: {
            makemaze(); int nsteps = 999;
            assert(traversePath(5,3,2,8,"2E1N3E2N",nsteps) == 0  &&  nsteps == 8);
                        } break; case 65: {
            makemaze(); int nsteps = 999;
            assert(traversePath(5,3,2,8,"2E1N3E3N",nsteps) == 1  &&  nsteps == 9);
			}
	}
}
void makemaze()
{
//   123456789012
// 1 ............
// 2 ......*.....
// 3 ............
// 4 ..*.........
// 5 ......*.....

        setSize(5,12);
        setWall(4,3);
        setWall(2,7);
        setWall(5,7);
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