#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <cstdlib>
#include <windows.h>
#include "dictionary.h"
#include "board.h"

using namespace std;

int menu() // opening text + instructions to use the program + create/load a puzzle
{
	string option;
	cout << "CROSSWORDS PUZZLE CREATOR" << endl; 
	cout << "=======================================" << endl; cout << endl;
	cout << "INSTRUCTIONS:" << endl;
	cout << "The options menu lets you create a board to play (1), or a load a pre-existing one(2)" << endl;
	cout << "You need to provide a dictionary to have words to put on the board" << endl;
	cout << "Position ( LCD / CTRL-Z = stop )\n LCD stands for Line Column and Direction" << endl;
	cout << "These are case-sensitive, Line and Direction must be input in upper-case, while Column must be input in lower-case" << endl;
	cout << "Input CTRL-Z on the position question to exit the program, you can choose to continue later or finish the board" << endl;
	cout << "Word ( - = remove / ? = help ) . . ?\n Input - to remove the word at the selected position/direction\n Input ? to get a possible word to place on the board" << endl;
	cout << "--------------------------" << endl;
	do // choose to create a new puzzle, or load an existing one
	{
		cout << "OPTIONS:\n 1 - Create puzzle\n 2 - Resume puzzle\n 0 - Exit \n\n Option? ";
		getline(cin, option);
		while (cin.eof()) 
		{
			cin.clear();
			cout << "Cannot exit the program using CTRL-Z" << endl;
			cout << "OPTIONS:\n 1 - Create puzzle\n 2 - Resume puzzle\n 0 - Exit \n\n Option? ";
			getline(cin,option);
		}
		if (option == "1")
			return 1; // return value to create a new board
		else if (option == "2")
			return 2; // return value to load an existing board
		else if (option == "0")
			exit(0); 
		else
		{
			cerr << "Invalid option! (select 0, 1, or 2)\n";
		}
	} 
	while (option != "1" && option != "2" && option != "0");
	return 1; 
}

int main()
{
	if (menu() == 1) // create a new board
	{
		cout << "-------------\n CREATE PUZZLE\n-------------\n";
		dictionary dic;
		board obj;
		obj.board_display();
		obj.board_input(dic);
		return 0;
	}
	else // load an existing board
	{
		dictionary dic;
		board obj(30, 30);
		obj.board_load();
		obj.board_display();
		obj.board_input(dic);
		return 0;
	}
}