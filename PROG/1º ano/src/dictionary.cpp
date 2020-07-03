#include "stdafx.h"
#include "dictionary.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

dictionary::dictionary() // function to extract dictionary words from a file
{
	string dic_name; 
	ifstream dic_file;

	cout << "Name of the dictionary file: " << endl;
	cin >> dic_name;
	while (cin.eof())
	{
		cin.clear();
		cout << "Cannot exit the program using CTRL-Z" << endl;
		cout << "Name of the dictionary file: " << endl;
		cin >> dic_name;
	}

	dic_file.open(dic_name);

	if (dic_file.fail())
	{
		cerr << "File not found!\n";
		system("pause");
		exit(1);
	}

	vector<string> syn; 
	string s; 
	size_t pos = 0;
	char delim1 = ':'; // separates the word from its synonyms
	char delim2 = ','; // separates synonyms
	string word; 
	string syno; 

	while (getline(dic_file, s)) // read every line in the file
	{
		if (s.length() != 0) 
		{
			pos = s.find(delim1); 
			word = s.substr(0, pos); // obtain the dictionary word in a line
			size_t temp = pos + 2; 
			for (size_t i = pos + 2; i < s.length(); i++)
			{
				if (s[i] == delim2) 
				{
					syno = s.substr(temp, i - temp); 
					syn.push_back(syno); // obtain synonyms of the current word
					temp = i + 2;
				}
				else if (s.find_last_of(',') <= i)
				{
					syno = s.substr(s.find_last_of(',') + 2, s.length());
					syn.push_back(syno); // obtain the last synonym of the current word
					break;
				}
			}
		}

		pair<string, vector<string>> p1(word, syn);
		diction.insert(p1); 
		syn.clear(); // to stop synonyms from previous words being listed as synonyms of the current word
	}
}

bool dictionary::dicwordexist(string word) // check if given word is in the dictionary
{
	for (auto it = diction.begin(); it != diction.end(); ++it) // go through the entire sorted dictionary words
	{
		string dicword = it->first;
		for (unsigned int i = 0; i <= dicword.length(); i++) 
		{
			dicword[i] = toupper(dicword[i]); // turn the word into uppercase to work with the board code
		}

		if (word == dicword) 
			return true;
	}
	cerr << "This word is not in the dictionary!" << endl;
	return false;
}

void dictionary::matchword(vector <string> wordsboard, string position, vector<vector<char>> seeboard, int l, int c) // get a list of valid words to put in a given position/direction
{
	string word;
	char line = position[0];
	char column = position[1];
	char direction = position[2];
	int rightcells = 0; // rightcells is the number of cells on the board that placing the word won't ruin

	for (auto it = diction.begin(); it != diction.end(); ++it) // go through the entire sorted dictionary words
	{
		int repeat = 0;
		word = it->first;

		for (unsigned int i = 0; i < word.length(); i++) // turn the word into uppercase to work with the board code
		{
			word[i] = toupper(word[i]);
		}

		for (unsigned int i = 0; i < wordsboard.size(); i++) // check if the word is in the board already
		{
			if (word == wordsboard.at(i))
				repeat = 1;
		}
		if (repeat != 1)
		{
			if (direction == 'H')
			{
				if (c - ((unsigned int)column - 97) >= word.size()) // check if word fits on the board
				{
					for (unsigned int i = 0; i < word.length(); i++)
					{
						if (seeboard[(int)line - 65][(int)column - 97 + i] != '.')
						{
							if (seeboard[int(line) - 65][int(column) - 97 + i] == word[i]) // check if the word's letter matches the board's letter
								rightcells = rightcells + 1;
						}
						else rightcells = rightcells + 1; // placing a letter on a . won't ruin the board
						
						if ((int(column) - 97 - 1) != -1) // check if the previous letter doesn't exit the board
						{
							if (seeboard[(int)line - 65][(int)column - 97 - 1] != '.' && seeboard[(int)line - 65][(int)column - 97 - 1] != '#')
								rightcells = rightcells - 1;
						}
						if ((int(column) - 97 + word.length()) != (int(column) - 97 + c + 1)) // check if the next letter doesn't exit the board
						{
							if (seeboard[(int)line - 65][(int)column - 97 + word.length()] != '.' && seeboard[(int)line - 65][(int)column - 97 + word.length()] != '#')
								rightcells = rightcells - 1;
						}
					}
				}
			}
			else if (direction == 'V')
			{
				if (l - ((unsigned int)line - 65) >= word.size()) // check if word fits on the board
				{
					for (unsigned int j = 0; j < word.length(); j++)
					{
						if (seeboard[(int)line - 65 + j][(int)column - 97] != '.')
						{
							if (seeboard[int(line) - 65 + j][int(column) - 97] == word[j]) // check if the word's letter matches the board's letter
								rightcells = rightcells + 1;
						}
						else rightcells = rightcells + 1; // placing a letter on a . won't ruin the board
						
						if ((int(line) - 65 - 1) != -1) // check if the previous letter doesn't exit the board
						{
							if (seeboard[(int)line - 65 - 1][(int)column - 97] != '.' && seeboard[(int)line - 65 - 1][(int)column - 97] != '#')
								rightcells = rightcells - 1;
						}
						
						if ((int(line) - 65 + word.length()) != (int(line) - 65 + l + 1)) // check if the next letter doesn't exit the board
						{
							if (seeboard[(int)line - 65 + word.length()][(int)column - 97] != '.' && seeboard[(int)line - 65 + word.length()][(int)column - 97] != '#')
								rightcells = rightcells - 1;
						}
					}
				}
			}
		}
		if (rightcells == word.size())
		{
			cout << word << endl;
		}
		rightcells = 0;
	}
}
