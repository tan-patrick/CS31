
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cassert>

using namespace std;
bool check(int b);
int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int rotateRight(string a[], int n, int pos);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int partition(string a[], int n, string separator);


string c[6] = {
	"alpha", "beta", "beta", "delta", "gamma", "gamma"
};

bool partitioncheck(const string a[], int n, int p, string separator)
{
	for (int k = 0; k < p; k++)
		if (a[k] >= separator)
			return false;
	for ( ; p < n  &&  a[p] == separator; p++)
		;
	for (int k = p; k < n; k++)
		if (a[k] <= separator)
			return false;
	string b[100];
	copy(a,a+n,b);
	sort(b,b+n);
	return equal(b,b+n,c);
}

void testone(int n)
{
	const int N = 6;

      // Act as if  a  were declared:
      //   string a[6] = {
      //       "alpha", "beta", "gamma", "gamma", "beta", "delta"
      //   };
      // This is done in a way that will probably cause a crash if
      // a[-1] or a[6] is accessed:  We place garbage in those positions.
	string aa[1+N+1] = {
		"", "alpha", "beta", "gamma", "gamma", "beta", "delta", ""
	};
	string* a = &aa[1];
	a[-1].string::~string();
	a[N].string::~string();
	fill_n(reinterpret_cast<char*>(&a[-1]), sizeof(a[-1]), 0xEF);
	fill_n(reinterpret_cast<char*>(&a[N]), sizeof(a[N]), 0xEF);

	string b[N] = {
		"alpha", "beta", "gamma", "delta", "beta", "delta"
	};

	switch (n)
	{
			         case  1: {
		assert(appendToAll(a, -1, "rho") == -1 && a[0] == "alpha");
			} break; case  2: {
		assert(appendToAll(a, 0, "rho") == 0 && a[0] == "alpha");
			} break; case  3: {
		assert(appendToAll(a, 1, "rho") == 1 && a[0] == "alpharho" &&
							a[1] == "beta");
			} break; case  4: {
		assert(appendToAll(a, 6, "rho") == 6 && a[0] == "alpharho" &&
			a[1] == "betarho" && a[2] == "gammarho" &&
			a[3] == "gammarho" && a[4] == "betarho" &&
			a[5] == "deltarho");
			} break; case  5: {
		assert(lookup(a, -1, "alpha") == -1);
			} break; case  6: {
		assert(lookup(a, 0, "alpha") == -1);
			} break; case  7: {
		assert(lookup(a, 1, "alpha") == 0);
			} break; case  8: {
		assert(lookup(a, 6, "delta") == 5);
			} break; case  9: {
		assert(lookup(a, 6, "beta") == 1);
			} break; case 10: {
		assert(lookup(a, 6, "zeta") == -1);
			} break; case 11: {
		assert(positionOfMax(a, -1) == -1);
			} break; case 12: {
		assert(positionOfMax(a, 0) == -1);
			} break; case 13: {
		assert(positionOfMax(a, 1) == 0);
			} break; case 14: {
		assert(positionOfMax(a, 3) == 2);
			} break; case 15: {
		assert(positionOfMax(a, 6) == 2);
			} break; case 16: {
		assert(positionOfMax(a+3, 3) == 0);
			} break; case 17: {
		a[0] = "";
		a[1] = " ";
		a[2] = "";
		assert(positionOfMax(a, 3) == 1);
			} break; case 18: {
		assert(rotateLeft(a, -1, 0) == -1 &&
				a[0] == "alpha" && a[1] == "beta");
			} break; case 19: {
		assert(rotateLeft(a, 6, -1) == -1 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 20: {
		assert(rotateLeft(a, 6, 6) == -1 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 21: {
		assert(rotateLeft(a, 0, 0) == -1 &&
				a[0] == "alpha" && a[1] == "beta");
			} break; case 22: {
		assert(rotateLeft(a, 1, 0) == 0 &&
				a[0] == "alpha" && a[1] == "beta");
			} break; case 23: {
		assert(rotateLeft(a, 6, 0) == 0 &&
			a[0] == "beta" && a[1] == "gamma" && a[2] == "gamma" &&
			a[3] == "beta" && a[4] == "delta" && a[5] == "alpha");
			} break; case 24: {
		assert(rotateLeft(a, 6, 5) == 5 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 25: {
		assert(rotateLeft(a, 6, 3) == 3 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "beta" && a[4] == "delta" && a[5] == "gamma");
			} break; case 26: {
		assert(rotateLeft(a, 5, 3) == 3 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "beta" && a[4] == "gamma" && a[5] == "delta");
			} break; case 27: {
		assert(rotateRight(a, -1, 0) == -1 &&
				a[0] == "alpha" && a[1] == "beta");
			} break; case 28: {
		assert(rotateRight(a, 6, -1) == -1 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 29: {
		assert(rotateRight(a, 6, 6) == -1 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 30: {
		assert(rotateRight(a, 0, 0) == -1 &&
				a[0] == "alpha" && a[1] == "beta");
			} break; case 31: {
		assert(rotateRight(a, 1, 0) == 0 &&
				a[0] == "alpha" && a[1] == "beta");
			} break; case 32: {
		assert(rotateRight(a, 6, 0) == 0 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 33: {
		assert(rotateRight(a, 6, 5) == 5 &&
			a[0] == "delta" && a[1] == "alpha" && a[2] == "beta" &&
			a[3] == "gamma" && a[4] == "gamma" && a[5] == "beta");
			} break; case 34: {
		assert(rotateRight(a, 5, 3) == 3 &&
			a[0] == "gamma" && a[1] == "alpha" && a[2] == "beta" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 35: {
		assert(flip(a, -1) == -1 && a[0] == "alpha");
			} break; case 36: {
		assert(flip(a, 0) == 0 && a[0] == "alpha");
			} break; case 37: {
		assert(flip(a, 1) == 1 && a[0] == "alpha" &&
					a[1] == "beta");
			} break; case 38: {
		assert(flip(a, 2) == 2 && a[0] == "beta" &&
					a[1] == "alpha" && a[2] == "gamma");
			} break; case 39: {
		assert(flip(a, 5) == 5 && a[0] == "beta" &&
			a[1] == "gamma" && a[2] == "gamma" && a[3] == "beta" &&
			a[4] == "alpha" && a[5] == "delta");
			} break; case 40: {
		a[2] = "zeta";
		assert(flip(a,6) == 6 && a[0] == "delta" && a[1] == "beta" &&
			a[2] == "gamma" && a[3] == "zeta" && a[4] == "beta" &&
			a[5] == "alpha");
			} break; case 41: {
		assert(differ(a, -1, b, 6) == -1);
			} break; case 42: {
		assert(differ(a, 6, b, -1) == -1);
			} break; case 43: {
		assert(differ(a, 0, b, 0) == 0);
			} break; case 44: {
		assert(differ(a, 3, b, 3) == 3);
			} break; case 45: {
		assert(differ(a, 3, b, 2) == 2);
			} break; case 46: {
		assert(differ(a, 2, b, 3) == 2);
			} break; case 47: {
		assert(differ(a, 6, b, 6) == 3);
			} break; case 48: {
		assert(subsequence(a, -1, b, 6) == -1);
			} break; case 49: {
		assert(subsequence(a, 6, b, -1) == -1);
			} break; case 50: {
		assert(subsequence(a, 0, b, 6) == -1);
			} break; case 51: {
		assert(subsequence(a, 6, b, 0) == 0);
			} break; case 52: {
		assert(subsequence(a, 6, b, 1) == 0);
			} break; case 53: {
		assert(subsequence(a, 6, b+4, 2) == 4);
			} break; case 54: {
		assert(subsequence(a, 6, b+3, 1) == 5);
			} break; case 55: {
		assert(subsequence(a, 6, b+3, 2) == -1);
			} break; case 56: {
		assert(subsequence(a, 6, b+2, 2) == -1);
			} break; case 57: {
		assert(subsequence(a, 6, a, 6) == 0);
			} break; case 58: {
		assert(lookupAny(a, 6, b, -1) == -1);
			} break; case 59: {
		assert(lookupAny(a, -1, b, 6) == -1);
			} break; case 60: {
		assert(lookupAny(a, 0, b, 1) == -1);
			} break; case 61: {
		assert(lookupAny(a, 6, b, 0) == -1);
			} break; case 62: {
		assert(lookupAny(a, 1, b, 1) == 0);
			} break; case 63: {
		assert(lookupAny(a, 6, b+3, 3) == 1);
			} break; case 64: {
		assert(lookupAny(a, 4, b+3, 3) == 1);
			} break; case 65: {
		assert(lookupAny(a, 2, b+2, 2) == -1);
			} break; case 66: {
		assert(partition(a, -1, "beta") == -1 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 67: {
		assert(partition(a, 0, "beta") == 0 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 68: {
		assert(partition(a, 1, "aaa") == 0 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 69: {
		assert(partition(a, 1, "alpha") == 0 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 70: {
		assert(partition(a, 1, "zeta") == 1 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 71: {
		assert(partition(a, 2, "aaa") == 0 &&
			partitioncheck(a, 2, 0, "aaa") && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 72: {
		assert(partition(a, 2, "alpha") == 0 &&
			partitioncheck(a, 2, 0, "alpha") && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 73: {
		assert(partition(a, 2, "beta") == 1 &&
			partitioncheck(a, 2, 1, "beta") && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 74: {
		assert(partition(a, 2, "zeta") == 2 &&
			partitioncheck(a, 2, 2, "zeta") && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 75: {
		assert(partition(a, 6, "aaa") == 0 && partitioncheck(a, 6, 0, "aaa"));
			} break; case 76: {
		assert(partition(a, 6, "alpha") == 0 &&
			partitioncheck(a, 6, 0, "alpha"));
			} break; case 77: {
		assert(partition(a, 6, "beta") == 1 &&
			partitioncheck(a, 6, 1, "beta"));
			} break; case 78: {
		assert(partition(a, 6, "delta") == 3 &&
			partitioncheck(a, 6, 3, "delta"));
			} break; case 79: {
		assert(partition(a, 6, "gamma") == 4 &&
			partitioncheck(a, 6, 4, "gamma"));
			} break; case 80: {
		assert(partition(a, 6, "zeta") == 6 &&
			partitioncheck(a, 6, 6, "zeta"));
			} break; case 81: {
		a[2] = "mu";
		c[5] = "mu";
		assert(partition(a, 6, "mu") == 5 && partitioncheck(a, 6, 5, "mu"));
			} break; case 82: {
		assert(partition(a, 6, "chi") == 3 && partitioncheck(a, 6, 3, "chi"));
			} break; case 83: {
		// This case tested whether rotateLeft used an extra array
			} break; case 84: {
		// This case tested whether rotateRight used an extra array
			} break; case 85: {
		// This case tested whether flip used an extra array
			} break; case 86: {
		// This case tested whether partition used an extra array
			} break;
	}

	new (&a[-1]) string;
	new (&a[N]) string;
}

int main()
{
    cout << "Enter a test number (1 to 86): ";
    int n;
	for(;;){
    cin >> n;
    if (n < 1  ||  n > 86)
    {
	cout << "Bad test number" << endl;
	return 1;
	break;
    }
    testone(n);
    cout << "Passed test " << n << endl;
	}
}

int appendToAll(string a[], int n, string value)
{
	if(!check(n))
		return -1;
    for (int i = 0; i < n; i++)
	{
		a[i] += value;	//Addes the value to the end of each string
	}
	return n;
}

int lookup(const string a[], int n, string target)
{
	if(!check(n))
		return -1;
	for (int i = 0; i < n; i++)
	{
		if(a[i] == target)	//When the string is the same as the target, return the position
			return i;
	}
	return -1;
}

int positionOfMax(const string a[], int n)
{
	if(!check(n))
		return -1;
	string cur = "";
	int max = -1;
	for (int i = 0; i < n; i++)
	{
		if(cur < a[i])	//When current string is greater than previously greatest string
		{
			max = i;	//Set the max to the current position and set greatest string to current string
			cur = a[i];
		}
	}
	return max;
}

int rotateLeft(string a[], int n, int pos)
{
	if(!check(n))
		return -1;
	if(pos >= n)
		return -1;
	string save = a[pos];	//Save initial string
	for(int i = pos; i < n - 1; i++)
	{
		a[i] = a[i+1];	//Move strings left one space
	}
	a[n - 1] = save;	//Place overwritten string (initial string) to end of array
	return pos;
}

int rotateRight(string a[], int n, int pos)
{	
	if(!check(n))
		return -1;
	if(pos >= n)
		return -1;
	string save = a[pos];	//Save initial string
	for(int i = pos; i > 0; i--)
	{
		a[i] = a[i-1];	//Move strings right one space
	}
	a[0] = save;	//Place overwritten string (initial string) to start of array
	return pos;
}

int flip(string a[], int n)
{
	int end = n - 1;
	string temp = "";
	if(!check(n))
		return -1;
	for(int i = 0; i < end / 2; i++)	//Only go through half, or it will flip back to original
	{
		temp = a[end-i];	//Swap the places of the two strings
		a[end-i] = a[i];	//Use positions that are same distance from beginning and the end
		a[i] = temp;
	}
	return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
	if(!check(n1))
		return -1;
	if(!check(n2))
		return -1;
	int i = 0;
	while(i < n1 && i < n2)	//Repeatedly: i reaches either n1 or n2
	{
		if(a1[i] != a2[i])	//When the two are not equal, end the loop
			break;
		i++;
	}
	return i;
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
	if(!check(n1))
		return -1;
	if(!check(n2))
		return -1;
	int increment = 0;
	for(int i = 0; i <= n1 - n2; i++)
	{
		for(increment = 0; increment < n2; increment++)
		{
			if(a1[i + increment] != a2[increment])	//If the strings do not match, end the comparison
				break;
		}
		if(increment == n2)	//If all the strings matched, return the position of the first string
			return i;
	}
	return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
	if(!check(n1))
		return -1;
	if(!check(n2))
		return -1;
	for(int i = 0; i < n1; i++)
	{
		for(int j = 0; j < n2; j++)
			if(a1[i] == a2[j])
				return i;	//If any of the strings in a2 match a string in a1, return the position in a1
	}
	return -1;
}

int partition(string a[], int n, string separator)
{
	if(!check(n))
		return -1;
	int i = 0;
	for(int count = 0; count < n; count++)	//Ensure that the method will not run into an infinite loop
	{
		if(a[i] < separator)
		{
			rotateRight(a, n, i);	//When the string is less than separator, move it to front of array
			i++;	//Add i to move to next position, as the string is moved to the front of array
		}
		else if (a[i] > separator)
		{
			rotateLeft(a, n, i);	//When the string is greater than separator, move it to end of array (Do not increment i; Check same spot, as string will be different)
		}
		else
			i++;	//If the string is equal to the separator, only increment i
	}
	for(int b = 0; b < n; b++)
	{
		if(a[b] >= separator)	//Return the first position that the string is not less than separator
			return b;
	}
	return n;
}

bool check(int b)	//Ensures that the number input is not negative
{
	if(b < 0)
		return false;
	return true;
}