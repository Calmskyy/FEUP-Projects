#ifndef dictionary_H
#define dictionary_H
#include <string>
#include <vector>
#include <map>

using namespace std;

class dictionary
{
public:
	dictionary();
	bool dicwordexist(string w);
	void matchword(vector <string> wordsboard, string position, vector<vector<char>> seeboard, int l, int c);
private:
	map <string, vector<string>> diction; // dictionary words will be stored in here as pairs of <word, wordsynonyms>
};

#endif