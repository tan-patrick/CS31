#include <iostream>
#include <cassert>
#include <cctype>
#include <string>
#include <iostream>
#include <cstring>
using namespace std;

const int MAX_WORD_LENGTH = 20;

int normalizeCriteria(int distance[], char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int nCriteria);
int moveIntToEnd(int a[], int n, int pos);
int moveCharToEnd(char a[][MAX_WORD_LENGTH+1], int n, int pos);
void allLower(char c[][MAX_WORD_LENGTH + 1], int n);
bool letter(char l[][MAX_WORD_LENGTH + 1], int pos);
int similar(int dis[], char setOne[][MAX_WORD_LENGTH+1], char setTwo[][MAX_WORD_LENGTH+1], int criteria);
int computeScore(const int distance[], const char word1[][MAX_WORD_LENGTH+1], const char word2[][MAX_WORD_LENGTH+1], int nCriteria, const char document[]);

int normalizeCriteria(int distance[], char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int nCriteria)
{
	int endCriteria = nCriteria;
	int i = 0;
	
	allLower(word1, nCriteria);		//makes all words all lower case
	allLower(word2, nCriteria);
	endCriteria = similar(distance, word1, word2, nCriteria);  //checks for identical criteria

	while(i != endCriteria) //Moves criteria with non positive distances out of valid criteria
	{
		if(distance[i] <= 0)
		{
			moveIntToEnd(distance, nCriteria, i);
			moveCharToEnd(word1, nCriteria, i);
			moveCharToEnd(word2, nCriteria, i);
			endCriteria--;
		}
		else
			i++;
	}

	i = 0;

	while(i != endCriteria) //Moves criteria with an empty string out of valid criteria
	{
		if(word1[i][0] == '\0' || word2[i][0] == '\0')
		{
			moveIntToEnd(distance, nCriteria, i);
			moveCharToEnd(word1, nCriteria, i);
			moveCharToEnd(word2, nCriteria, i);
			endCriteria--;
		}
		else
			i++;
	}

	i = 0;

	while(i != endCriteria)  //Moves criteria with a non alphabetical character out of valid criteria
	{
		if(!letter(word1, i) || !letter(word2,i))
		{
			moveIntToEnd(distance, nCriteria, i);
			moveCharToEnd(word1, nCriteria, i);
			moveCharToEnd(word2, nCriteria, i);
			endCriteria--;
		}
		else
			i++;
	}

	for(int i = 0; i < endCriteria; i++)
		cout << distance[i] << " " << word1[i] << " " << word2[i] << endl;

	return endCriteria; //Returns number of valid criteria
}

int computeScore(const int distance[], const char word1[][MAX_WORD_LENGTH+1], const char word2[][MAX_WORD_LENGTH+1], int nCriteria, const char document[])
{
	int score = 0;

	char check[201][201]; //Creates two-dimensional array check (maximum number of document is 200, +1 for '0' '\0'
	int num = 0;
	int loc = 0;

	for(int k = 0; document[k] != '\0'; k++)  //Puts all of the words in the document into a normalized form
	{
		if(isalpha(document[k])) //Keeps on alphabeticals and makes them lower case
		{
			check[num][loc] = tolower(document[k]);
			loc++;
		}
		if(document[k] == ' ') //Controls the location in the array to keep the proper number of words in the correct order
		{
			check[num][loc] = '\0';
			while(!isalpha(document[k+1]) && (document[k+1] != '\0'))
				k++;
			if(document[k+1] != '\0')
			{
				loc = 0;
				num++;
			}
		}
	}
	check[num][loc] = '\0';
	bool exit = false;

	for(int j = 0; j < nCriteria; j++) //Counts number of criteria fulfilled
	{
		for(int i = 0; i <= num; i++)
		{
			if(exit == true) //Breaks out of loop when criteria was matched
			{
				exit = false;
				break;
			}
			if(strcmp(check[i], word1[j]) == 0) //Checks if criteria matched by a word in the document
			{
				for(int k = 1; k <= distance[j] && i + k <= num; k++)
				{
					if(strcmp(check[i+k], word2[j]) == 0) //Checks if second word shows up within distance
					{
						score++;
						exit = true;
						break;
					}
				}
			}
		}
	}

	return score;
}

int moveIntToEnd(int a[], int n, int pos)
{
	if(n < 0)
		return -1;
	if(pos >= n || pos < 0)
		return -1;
	int save = a[pos];	//Save initial integer
	for(int i = pos; i < n - 1; i++)
	{
		a[i] = a[i+1];	//Move array left one space
	}
	a[n - 1] = save;	//Place overwritten integer (initial integer) to end of array
	return 1;
}

int moveCharToEnd(char a[][MAX_WORD_LENGTH+1], int n, int pos)
{
	if(n < 0)
		return -1;
	if(pos >= n || pos < 0)
		return -1;
	char save[1][MAX_WORD_LENGTH+1]; //Saves initial string
	
	strcpy(save[0], a[pos]);
	for(int i = pos; i < n - 1; i++)
	{
		strcpy(a[i], a[i+1]); //Moves all strings left one space
	}
	strcpy(a[n - 1], save[0]); //Replaces string at end
	return 1;
}

void allLower(char c[][MAX_WORD_LENGTH + 1], int n)
{
	for(int i = 0; i != n; i++) //Makes all characters in the input array to lower case
	{
		for(int j = 0; j != MAX_WORD_LENGTH + 1 && c[i][j] != '\0'; j++) 
		{
			c[i][j] = tolower(c[i][j]);
		}
	}
}

bool letter(char l[][MAX_WORD_LENGTH + 1], int pos)
{
	int a = 0;
	while(l[pos][a] != '\0') //Checks if all characters are alphabetical
	{
		if(!isalpha(l[pos][a]))
		{
			return false;
		}
		a++;
	}
	return true;
}

int similar(int dis[], char setOne[][MAX_WORD_LENGTH+1], char setTwo[][MAX_WORD_LENGTH+1], int criteria)
{
	//Checks if the criteria are equal and moves the criteria with lesser distance out of valid criteria

	int startCriteria = criteria;

	for(int i = 0; i != criteria; i++)
	{
		for(int j = 0; j != criteria; j++)
		{
			if(j != i)
			{
				if(strcmp(setOne[i], setOne[j]) == 0 && strcmp(setTwo[i], setTwo[j]) == 0) 
				{
					if(dis[i] < dis[j])
					{
						moveIntToEnd(dis, startCriteria, i);
						moveCharToEnd(setOne, startCriteria, i);
						moveCharToEnd(setTwo, startCriteria, i);
						criteria--;
					}
					else
					{
						moveIntToEnd(dis, startCriteria, j);
						moveCharToEnd(setOne, startCriteria, j);
						moveCharToEnd(setTwo, startCriteria, j);
						criteria--;
					}
					j--;
				}
			}
		}
	}
	return criteria;
}

int d[3] =                      {    2,    1,    3 };
char w1[3][MAX_WORD_LENGTH+1] = { "aa", "bb", "cc" };
char w2[3][MAX_WORD_LENGTH+1] = { "dd", "ee", "ff" };

int e[2] =                      {    4,    4 };
char x1[2][MAX_WORD_LENGTH+1] = { "aa", "cc" };
char x2[2][MAX_WORD_LENGTH+1] = { "bb", "dd" };

const int THREE_LETTERS = 26*26*26;
int dd[THREE_LETTERS];
char ww1[THREE_LETTERS][MAX_WORD_LENGTH+1];
char ww2[THREE_LETTERS][MAX_WORD_LENGTH+1];

bool equals(int c, int dist, const char wd1[], const char wd2[])
{
	return d[c] == dist  &&  strcmp(w1[c], wd1) == 0  &&
						strcmp(w2[c], wd2) == 0;
}

void testone(int n)
{
	switch (n)
	{
			         case  1: {
		assert(normalizeCriteria(d, w1, w2, 0) == 0);
			} break; case  2: {
		assert(normalizeCriteria(d, w1, w2, 1) == 1  &&
					equals(0, 2, "aa", "dd"));
			} break; case  3: {
		d[0] = 0;
		assert(normalizeCriteria(d, w1, w2, 1) == 0);
			} break; case  4: {
		d[0] = 0;
		assert(normalizeCriteria(d, w1, w2, 2) == 1  &&
					equals(0, 1, "bb", "ee"));
			} break; case  5: {
		d[1] = 0;
		assert(normalizeCriteria(d, w1, w2, 2) == 1  &&
					equals(0, 2, "aa", "dd"));
			} break; case  6: {
		d[1] = 0;
		d[2] = 0;
		assert(normalizeCriteria(d, w1, w2, 3) == 1  &&
					equals(0, 2, "aa", "dd"));
			} break; case  7: {
		d[0] = 0;
		d[1] = 0;
		assert(normalizeCriteria(d, w1, w2, 3) == 1  &&
					equals(0, 3, "cc", "ff"));
			} break; case  8: {
		d[0] = 0;
		d[1] = 0;
		d[2] = 0;
		assert(normalizeCriteria(d, w1, w2, 3) == 0);
			} break; case  9: {
		strcpy(w1[1], "");
		assert(normalizeCriteria(d, w1, w2, 3) == 2  &&
					(equals(0, 2, "aa", "dd")  &&
					 equals(1, 3, "cc", "ff"))  ||
					(equals(1, 2, "aa", "dd")  &&
					 equals(0, 3, "cc", "ff")));
			} break; case 10: {
		strcpy(w2[1], "");
		assert(normalizeCriteria(d, w1, w2, 3) == 2  &&
					(equals(0, 2, "aa", "dd")  &&
					 equals(1, 3, "cc", "ff"))  ||
					(equals(1, 2, "aa", "dd")  &&
					 equals(0, 3, "cc", "ff")));
			} break; case 11: {
		strcpy(w1[1], "bb@");
		assert(normalizeCriteria(d, w1, w2, 3) == 2  &&
					(equals(0, 2, "aa", "dd")  &&
					 equals(1, 3, "cc", "ff"))  ||
					(equals(1, 2, "aa", "dd")  &&
					 equals(0, 3, "cc", "ff")));
			} break; case 12: {
		strcpy(w1[1], "bb ");
		assert(normalizeCriteria(d, w1, w2, 3) == 2  &&
					(equals(0, 2, "aa", "dd")  &&
					 equals(1, 3, "cc", "ff"))  ||
					(equals(1, 2, "aa", "dd")  &&
					 equals(0, 3, "cc", "ff")));
			} break; case 13: {
		strcpy(w1[1], "bBBb");
		assert(normalizeCriteria(d, w1, w2, 2) == 2  &&
					(equals(0, 2, "aa", "dd")  &&
					 equals(1, 1, "bbbb", "ee"))  ||
					(equals(1, 2, "aa", "dd")  &&
					 equals(0, 1, "bbbb", "ee")));
			} break; case 14: {
		strcpy(w1[1], "bBBb");
		strcpy(w2[1], "EeEeE");
		assert(normalizeCriteria(d, w1, w2, 2) == 2  &&
					(equals(0, 2, "aa", "dd")  &&
					 equals(1, 1, "bbbb", "eeeee"))  ||
					(equals(1, 2, "aa", "dd")  &&
					 equals(0, 1, "bbbb", "eeeee")));
			} break; case 15: {
		strcpy(w2[1], "bb");
		assert(normalizeCriteria(d, w1, w2, 2) == 2  &&
					(equals(0, 2, "aa", "dd")  &&
					 equals(1, 1, "bb", "bb"))  ||
					(equals(1, 2, "aa", "dd")  &&
					 equals(0, 1, "bb", "bb")));
			} break; case 16: {
		strcpy(w1[1], "aa");
		strcpy(w2[1], "dd");
		assert(normalizeCriteria(d, w1, w2, 3) == 2  &&
					(equals(0, 2, "aa", "dd")  &&
					 equals(1, 3, "cc", "ff"))  ||
					(equals(1, 2, "aa", "dd")  &&
					 equals(0, 3, "cc", "ff")));
			} break; case 17: {
		strcpy(w1[1], "aa");
		strcpy(w2[1], "dd");
		d[1] = 1;
		assert(normalizeCriteria(d, w1, w2, 3) == 2  &&
					(equals(0, 2, "aa", "dd")  &&
					 equals(1, 3, "cc", "ff"))  ||
					(equals(1, 2, "aa", "dd")  &&
					 equals(0, 3, "cc", "ff")));
			} break; case 18: {
		strcpy(w1[1], "aa");
		strcpy(w2[1], "dd");
		d[1] = 5;
		assert(normalizeCriteria(d, w1, w2, 3) == 2  &&
					(equals(0, 5, "aa", "dd")  &&
					 equals(1, 3, "cc", "ff"))  ||
					(equals(1, 5, "aa", "dd")  &&
					 equals(0, 3, "cc", "ff")));
			} break; case 19: {
		strcpy(w1[1], "aa");
		strcpy(w2[1], "dd");
		strcpy(w1[2], "aa");
		strcpy(w2[2], "dd");
		assert(normalizeCriteria(d, w1, w2, 3) == 1  &&
					equals(0, 3, "aa", "dd"));
			} break; case 20: {
		strcpy(w1[2], "aa");
		strcpy(w2[2], "dd");
		d[1] = 0;
		assert(normalizeCriteria(d, w1, w2, 3) == 1  &&
					equals(0, 3, "aa", "dd"));
			} break; case 21: {
		strcpy(w1[1], "abcdefghijklmnopqrst");
		strcpy(w2[1], "abcdefghijklmnopqrsu");
		d[0] = 0;
		assert(normalizeCriteria(d, w1, w2, 2) == 1  &&
				equals(0, 1, "abcdefghijklmnopqrst",
						"abcdefghijklmnopqrsu"));
			} break; case 22: {
		strcpy(w2[0], "DD");
		strcpy(w1[1], "AA");
		strcpy(w2[1], "dD");
		assert(normalizeCriteria(d, w1, w2, 3) == 2  &&
					(equals(0, 2, "aa", "dd")  &&
					 equals(1, 3, "cc", "ff"))  ||
					(equals(1, 2, "aa", "dd")  &&
					 equals(0, 3, "cc", "ff")));
			} break; case 23: {
		int dx[7] = { 2, 4, 1, 3, 2, 1, 13 };
		char w1x[7][MAX_WORD_LENGTH+1] = { "mad", "deranged",
			"NEFARIOUS", "half-witted", "deranged", "Nefarious",
			"plot" };
		char w2x[7][MAX_WORD_LENGTH+1] = { "scientist", "robot",
			"PLOT", "assistant", "robot", "plot", "mad" };
		assert(normalizeCriteria(dx, w1x, w2x, 7) == 4);
			} break; case 24: {
		assert(computeScore(e, x1, x2, 2, "") == 0);
			} break; case 25: {
		assert(computeScore(e, x1, x2, 2, " ") == 0);
			} break; case 26: {
		assert(computeScore(e, x1, x2, 2, "aa bb") == 1);
			} break; case 27: {
		e[0] = 1;
		assert(computeScore(e, x1, x2, 2, "aa bb") == 1);
			} break; case 28: {
		e[0] = 1;
		assert(computeScore(e, x1, x2, 2, "aa     bb") == 1);
			} break; case 29: {
		assert(computeScore(e, x1, x2, 2, " aa bb") == 1);
			} break; case 30: {
		assert(computeScore(e, x1, x2, 2, "aa bb ") == 1);
			} break; case 31: {
		assert(computeScore(e, x1, x2, 2, "aa bb cc dd xx") == 2);
			} break; case 32: {
		assert(computeScore(e, x1, x2, 1, "aa bb cc dd xx") == 1);
			} break; case 33: {
		assert(computeScore(e, x1, x2, 2, "aa xx xx bb cc dd xx") == 2);
			} break; case 34: {
		assert(computeScore(e, x1, x2, 2, "aa xx xx xx bb cc dd xx") == 2);
			} break; case 35: {
		assert(computeScore(e, x1, x2, 2, "aa xx xx xx xx bb cc dd xx") == 1);
			} break; case 36: {
		e[0] = 1;
		e[1] = 1;
		assert(computeScore(e, x1, x2, 2, "aa xx bb cc dd xx") == 1);
			} break; case 37: {
		e[0] = 2;
		e[1] = 2;
		assert(computeScore(e, x1, x2, 2, "aa cc bb dd xx") == 2);
			} break; case 38: {
		assert(computeScore(e, x1, x2, 2, "aa bb aa bb cc dd xx") == 2);
			} break; case 39: {
		assert(computeScore(e, x1, x2, 2, "aa aa bb bb cc dd xx") == 2);
			} break; case 40: {
		assert(computeScore(e, x1, x2, 2, "aA bb cc dd xx") == 2);
			} break; case 41: {
		assert(computeScore(e, x1, x2, 2, "aa @@ ## $$ %% ^^ bb cc dd xx") == 2);
			} break; case 42: {
		assert(computeScore(e, x1, x2, 2, "aa b@@b cc dd xx") == 2);
			} break; case 43: {
		assert(computeScore(e, x1, x2, 2, "aa b123456789012345678901234567890b cc dd xx") == 2);
			} break; case 44: {
		e[0] = 1;
		assert(computeScore(e, x1, x2, 2, "aa abcdefghijklmnopqrstuvwxyz bb cc dd xx") == 1);
			} break; case 45: {
		e[0] = 2;
		assert(computeScore(e, x1, x2, 2, "aa abcdefghijklmnopqrstuvwxyz bb cc dd xx") == 2);
			} break; case 46: {
		strcpy(x1[0], "abcdefghijklmnopqrst");
		assert(computeScore(e, x1, x2, 2, "abcdefghijklmnopqrst bb cc dd xx") == 2);
			} break; case 47: {
		strcpy(x1[0], "abcdefghijklmnopqrst");
		assert(computeScore(e, x1, x2, 2, "abcdefghijklmnopqrstu bb cc dd xx") == 1);
			} break; case 48: {
		assert(computeScore(e, x1, x2, 2, "aaa bb cc dd xx") == 1);
			} break; case 49: {
		assert(computeScore(e, x1, x2, 2, "aa@bb cc dd xx") == 1);
			} break; case 50: {
		assert(computeScore(e, x1, x2, 2, "aa bb@cc dd xx") == 0);
			} break; case 51: {
		for (int k = 0; k < THREE_LETTERS; k++)
		{
			dd[k] = k % 2;
			strcpy(ww1[k], "a");
			strcpy(ww2[k], "aaa");
			int kk = k;
			ww2[k][2] += kk % 26;
			kk /= 26;
			ww2[k][1] += kk % 26;
			kk /= 26;
			ww2[k][0] += kk;
		}
		assert(normalizeCriteria(dd, ww1, ww2, THREE_LETTERS) == THREE_LETTERS / 2);
		for (int k = 0; k < THREE_LETTERS / 2; k++)
			assert(dd[k] == 1 && strcmp(ww1[k], "a") == 0 &&
				islower(ww2[k][2]) &&
				(ww2[k][2] - 'a') % 2 == 1);
			} break; case 52: {
		for (int k = 0; k < THREE_LETTERS; k++)
		{
			dd[k] = 1;
			strcpy(ww1[k], "a");
			strcpy(ww2[k], "aaa");
			int kk = k;
			ww2[k][2] += kk % 26;
			kk /= 26;
			ww2[k][1] += kk % 26;
			kk /= 26;
			ww2[k][0] += kk;
		}
		assert(computeScore(dd, ww1, ww2, THREE_LETTERS,
				"a aaa a iaa a pzz a zzz") == 4);
		assert(computeScore(dd, ww1, ww2, THREE_LETTERS,
				"a aaaa a iaaa a pzzz a zzzz") == 0);
			} break;
	}
}

int main()
{
    cout << "Enter a test number (1 to 52): ";
    int n;
    cin >> n;
    if (n < 1  ||  n > 52)
    {
        cout << "Bad test number" << endl;
        return 1;
    }
    testone(n);
    cout << "Passed test " << n << endl;
}