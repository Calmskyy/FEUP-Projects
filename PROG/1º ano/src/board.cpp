#include "stdafx.h"
#include "board.h"
#include <vector>
#include <iostream>
#include "dictionary.h"
#include <windows.h>
#include <iomanip>

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

void setcolor(unsigned int color, unsigned int background_color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	if (background_color == BLACK)
		SetConsoleTextAttribute(hCon, color);
	else
		SetConsoleTextAttribute(hCon, color | BACKGROUND_BLUE | BACKGROUND_GREEN |
			BACKGROUND_RED);
}

board::board() // constructor used to create a new board
{
	cout << "Board size (lines columns)? ";
	cin >> l >> c;
	cin.ignore(1000, '\n');
	while (cin.eof()) 
	{
		cin.clear();
		cout << "Cannot exit the program using CTRL-Z" << endl;
		cout << "Board size (lines columns)? ";
		cin >> l >> c;
		cin.ignore(1000, '\n');
	}
	while (cin.fail())
	{
		cerr << "Invalid input! (number input only)" << endl;
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Board size (lines columns)? ";
		cin >> l >> c;
		cin.ignore(1000, '\n');
		while (cin.eof())
		{
			cin.clear();
			cout << "Cannot exit the program using CTRL-Z" << endl;
			cout << "Board size (lines columns)? ";
			cin >> l >> c;
			cin.ignore(1000, '\n');
		}
	}
	while (l > 26 || c > 26)
	{
		cout << "Can't create a board that big\n";
		cout << "Board size (lines columns)? ";
		cin >> l >> c;
		cin.ignore(1000, '\n');
		while (cin.eof())
		{
			cin.clear();
			cout << "Cannot exit the program using CTRL-Z" << endl;
			cout << "Board size (lines columns)? ";
			cin >> l >> c;
			cin.ignore(1000, '\n');
		}
		while (cin.fail())
		{
			cerr << "Invalid input! (number input only)" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Board size (lines columns)? ";
			cin >> l >> c;
			cin.ignore(1000, '\n');
			while (cin.eof())
			{
				cin.clear();
				cout << "Cannot exit the program using CTRL-Z" << endl;
				cout << "Board size (lines columns)? ";
				cin >> l >> c;
				cin.ignore(1000, '\n');
			}
		}
	}

	vector <char> temp;

	for (unsigned int i = 0; i <= l; i++) // create a new board filled with dots
	{
		for (unsigned int j = 0; j <= c; j++)
		{
			temp.push_back('.');
		}
		board_contents.push_back(temp);
	}
}

board::board(int nlin, int ncol) // constructor used to load an existing board
{
	vector <char> temp;
	l = nlin;
	c = ncol;

	for (unsigned int i = 0; i <= l; i++) // create a new board filled with dots, which will be replaced by the loaded one after this function
	{
		for (unsigned int j = 0; j <= c; j++)
		{
			temp.push_back('.');
		}
		board_contents.push_back(temp);
	}
}

bool board::board_valid(dictionary &dic) // check if the word fits in the given position and direction
{
	char line = position[0];
	char column = position[1];
	char direction = position[2];
	int rightcells = 0; // rightcells is the number of cells on the board that placing the word won't ruin

	for (unsigned int i = 0; i < board_words.size(); i++) // check if the word is already on the board
	{
		if (word == board_words.at(i))
		{
			cout << "That word is already in the puzzle! ";
			return false;
		}
	}

	if (!dic.dicwordexist(word))
		board_input (dic);

	if (direction == 'H')
	{
		if (c - ((unsigned int)column - 97) >= word.size()) // check if word fits on the board
		{
			for (unsigned int i = 0; i < word.length(); i++)
			{
				if (board_contents[(int)line - 65][(int)column - 97 + i] != '.')
				{
					if (board_contents[int(line) - 65][int(column) - 97 + i] == word[i]) // check if the word's letter matches the board's letter
						rightcells = rightcells + 1;
				}
				else rightcells = rightcells + 1; // placing a letter on a . won't ruin the board

				if ((int(column) - 97 - 1) != -1) // check if the previous letter doesn't exit the board
				{
					if (board_contents[(int)line - 65][(int)column - 97 - 1] != '.' && board_contents[(int)line - 65][(int)column - 97 - 1] != '#')
						rightcells = rightcells - 1;
				}
				
				if ((int(column) - 97 + word.length()) != (int(column) - 97 + c + 1)) // check if the next letter doesn't exit the board
				{
					if (board_contents[(int)line - 65][(int)column - 97 + word.length()] != '.' && board_contents[(int)line - 65][(int)column - 97 + word.length()] != '#')
						rightcells = rightcells - 1;
				}
			}
		}
		else {
			cout << "Word doesn't fit! " << endl;
			return false;
		}
	}
	else if (direction == 'V')
	{
		if (l - ((unsigned int)line - 65) >= word.size()) 
		{
			for (unsigned int j = 0; j < word.length(); j++)
			{
				if (board_contents[(int)line - 65 + j][(int)column - 97] != '.')
				{
					if (board_contents[int(line) - 65 + j][int(column) - 97] == word[j])
						rightcells = rightcells + 1;
				}
				else rightcells = rightcells + 1;

				if ((int(line) - 65 - 1) != -1) 
				{
					if (board_contents[(int)line - 65 - 1][(int)column - 97] != '.' && board_contents[(int)line - 65 - 1][(int)column - 97] != '#')
						rightcells = rightcells - 1;
				}
				if ((int(line) - 65 + word.length()) != (int(line) - 65 + l + 1)) 
				{
					if (board_contents[(int)line - 65 + word.length()][(int)column - 97] != '.' && board_contents[(int)line - 65 + word.length()][(int)column - 97] != '#')
						rightcells = rightcells - 1;
				}
			}
		}
		else {
			cout << "Word doesn't fit! " << endl;
			return false;
		}

	}
	if (rightcells == word.size())
	{
		return true;
	}
	else return false;
}

void board::board_display() // display the board on the screen
{
	unsigned int col = 'a' + c;
	unsigned int lin = 'A' + l;
	vector <char> temp;

	cout << "   ";
	for (size_t q = 'a'; q < col; q++)
	{
		setcolor(4, 0);
		cout << (char)q << " ";
	}
	cout << endl;
	for (unsigned int i = 0; i < l; i++)
	{
		unsigned int t = i + 'A';
		setcolor(4, 0);
		cout << (char)t << " ";

		setcolor(0, 15);
		cout << " ";
		for (unsigned int j = 0; j < c; j++)
		{
			if (board_contents.at(i).at(j) == '#')
			{
				setcolor(15, 0);
				cout << board_contents.at(i).at(j);
				setcolor(0, 15);
				cout << " ";
			}
			else
			{
				setcolor(0, 15);
				cout << board_contents.at(i).at(j) << " ";
			}
		}
		cout << endl;
	}
	setcolor(15, 0);
}

void board::board_input(dictionary &dic) // asks for position and word input and calls the appropriate functions to deal with the input
{
	int dots = 0;
	int verif = 0;
	
	for (unsigned int i = 0; i < l; i++) 
	{
		for (unsigned int j = 0; j < c; j++)
		{
			if (board_contents[i][j] == '.')
				dots++;
		}
	}

	if (dots == 0) // check if board is full // talvez adicionar um finalcheck();
	{
		cout << "The board is full!" << endl;
		cout << "Do you wish to save your work and resume later (1) or finish the board (2)?" << endl;
		cin >> verif;
		while (cin.eof())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Cannot exit the program using CTRL-Z" << endl;
			cout << "Do you wish to save your work and resume later (1) or finish the board (2)?" << endl;
			cin >> verif;
		}
		while (cin.fail())
		{
			cerr << "Invalid input! (number input only)" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Do you wish to save your work and resume later (1) or finish the board (2)?" << endl;
			cin >> verif;
		}

		if (verif == 1)
			board_save(1); // save and resume later
		else if (verif == 2)
		{
			for (unsigned int i = 0; i <= l; i++)
			{
				for (unsigned int j = 0; j <= c; j++)
				{
					if (board_contents.at(i).at(j) == '.')
					{
						board_contents[i][j] = '#';
					}
				}
			}
			board_display();
			board_save(2); // finish the board
		}
		exit(0);
	}

	cout << "Position ( LCD / CTRL-Z = stop )? ";
	cin >> position;
	if (cin.eof())
	{
		cout << "Do you wish to save your work and resume later (1) or finish the board (2)?" << endl;
		cin.clear();
		cin >> verif;
		while (cin.eof())
		{
			cin.clear();
			cout << "Cannot exit the program using CTRL-Z" << endl;
			cout << "Do you wish to save your work and resume later (1) or finish the board (2)?" << endl;
			cin >> verif;
		}

		if (verif == 1)
			board_save(1);
		else if (verif == 2)
		{
			for (unsigned int i = 0; i <= l; i++)
			{
				for (unsigned int j = 0; j <= c; j++)
				{
					if (board_contents.at(i).at(j) == '.')
					{
						board_contents[i][j] = '#';
					}
				}
			}
			board_display();
			board_save(2);
		}
		exit(0);
	}

	if (position.size() != 3)
	{
		cout << "Invalid position input! (must consist of 3 letters)" << endl;
		board_input(dic);
	}

	char line = position[0];
	char column = position[1];
	char direction = position[2];

	int errors = 0;

	if (!isupper(line))
	{
		cout << "Line must be an upper-case letter!" << endl;
		errors++;
	}

	if (!islower(column))
	{
		cout << "Column must be a lower-case letter!" << endl;
		errors++;
	}
	
	if (direction != 'V' && direction != 'H')
	{
		cout << "Invalid direction! (must be V or H)" << endl;
		errors++;
	}

	if (errors > 0)
		board_input(dic);
	
	cout << "Word ( - = remove / ? = help ) .. ? ";
	cin >> word;
	while (cin.eof())
	{
		cin.clear();
		cout << "Cannot exit the program using CTRL-Z" << endl;
		cout << "Word ( - = remove / ? = help ) .. ? ";
		cin >> word;
	}
	for (unsigned int i = 0; i <= word.length(); i++)
	{
		word[i] = toupper(word[i]); // words on board are always in uppercase letters
	}
	

	if (word == "-")
	{
		board_remove();
		board_display();
		board_input(dic);
	}

	else if (word == "?")
	{
		dic.matchword(board_words, position, board_contents, l, c);
		board_display();
		board_input(dic);
	}

	else if (board_valid(dic)) 
	{
		if (direction == 'V') // places the word on the board vertically
		{
			for (unsigned int i = 0; i < word.length(); i++)
			{
				board_contents[int(line) - 65 + i][int(column) - 97] = word[i];
				if ((int(line) - 65 - 1) != -1)
					board_contents[int(line) - 65 - 1][int(column) - 97] = '#';
				if ((int(line) - 65 - 1) != (int(line) + 1))
					board_contents[int(line) - 65 + word.length()][int(column) - 97] = '#';
			}
			board_words.push_back(word);
			posit.push_back(position);
			board_display();
			board_input(dic);

		}
		else if (direction == 'H') // places the word on the board vertically
		{
			for (unsigned int i = 0; i < word.length(); i++)
			{
				board_contents[int(line) - 65][int(column) - 97 + i] = word[i];
				if ((int(column) - 97 - 1) != -1)
					board_contents[int(line) - 65][int(column) - 97 - 1] = '#';
				if ((int(column) - 97 - 1) != (int(column) + 1))
					board_contents[int(line) - 65][int(column) - 97 + word.length()] = '#';
			}
			board_words.push_back(word);
			posit.push_back(position);
			board_display();
			board_input(dic);
		}
	}
	else
	{
		cout << "Invalid word!" << endl;
		board_input(dic);
	}
}

void board::board_load() // load an existing board
{
	int finish_mode;
	string load_name;
	string s;
	string sub;
	vector <string> file_content;
	
	cout << "Existing boards:\n";

	seq_fileIn.open("sequenceFile.txt", ios::in); // used to automatically display every board

	if (seq_fileIn.is_open())
		seq_fileIn >> file_seq;
	else
	{
		cout << "There are no saved boards!\n"; 
		system("pause");
		exit(0);
	}
	
	for (unsigned int i = 1; i <= file_seq; i++)
	{
		cout << "b";
		cout << fixed << setprecision(2) << setfill('0');
		cout << setw(3) << i << endl;
	}

	
	cout << "Which board do you want to load? (bXXX.txt)" << endl;
	cin >> load_name;
	while (cin.eof())
	{
		cin.clear();
		cout << "Cannot exit the program using CTRL-Z" << endl;
		cout << "Which board do you want to load? (bXXX.txt)" << endl;
		cin >> load_name;
	}

	load_file.open(load_name);

	while (load_file.fail())
	{
		cerr << "File not found!" << endl;
		cout << "Which board do you want to load? (bXXX.txt)" << endl;
		cin >> load_name;
		while (cin.eof())
		{
			cin.clear();
			cout << "Cannot exit the program using CTRL-Z" << endl;
			cout << "Which board do you want to load? (bXXX.txt)" << endl;
			cin >> load_name;
		}
		load_file.open(load_name);
	}

	while (getline(load_file, s))
	{
		if (s.length() != 0)
		{
			file_content.push_back(s);
		}
	}

	int temp = 0;

	l = stoi(file_content.at(0), nullptr, 10);
	c = stoi(file_content.at(1), nullptr, 10);
	finish_mode = stoi(file_content.at(2), nullptr, 10); // check if it was finished to resume, or finished filled with #
	s = file_content.at(3);

	for (unsigned int i = 0; i < s.size(); i++)
	{
		if (s[i] == ' ')
		{
			sub = s.substr(temp, i - temp);

			board_words.push_back(sub);
			temp = i + 1;
		}
	}

	temp = 0;
	s = file_content.at(4);

	for (unsigned int i = 0; i < s.size(); i++)
	{
		if (s[i] == ' ')
		{
			sub = s.substr(temp, i - temp);

			posit.push_back(sub);
			temp = i + 1;
		}
	}

	for (unsigned int i = 0; i <= l; i++)
	{
		for (unsigned int j = 0; j <= c; j++)
		{
			board_contents.at(i).at(j) = '.';
		}
	}

	for (unsigned int i = 0; i < posit.size(); i++) // rebuilds the board
	{
		string repos = posit.at(i);
		string reword = board_words.at(i);

		char line = repos[0];
		char column = repos[1];
		char direction = repos[2];

		if (direction == 'V')
		{
			for (unsigned int i = 0; i <= reword.length(); i++)
			{
				board_contents[int(line) - 65 + i][int(column) - 97] = reword[i];
				if ((int(line) - 65 - 1) != -1)
					board_contents[int(line) - 65 - 1][int(column) - 97] = '#';
				if ((int(line) - 65 - 1) != (int(line) + 1))
					board_contents[int(line) - 65 + reword.length()][int(column) - 97] = '#';
			}
		}
		else if (direction == 'H')
		{
			for (unsigned int i = 0; i <= reword.length(); i++)
			{
				board_contents[int(line) - 65][int(column) - 97 + i] = reword[i];
				if ((int(column) - 97 - 1) != -1)
					board_contents[int(line) - 65][int(column) - 97 - 1] = '#';
				if ((int(column) - 97 - 1) != (int(column) + 1))
					board_contents[int(line) - 65][int(column) - 97 + reword.length()] = '#';
			}
		}
	}

	if (finish_mode == 2)
		for (unsigned int i = 0; i <= l; i++)
		{
			for (unsigned int j = 0; j <= c; j++)
			{
				if (board_contents.at(i).at(j) == '.')
				{
					board_contents[i][j] = '#';
				}
			}
		}
}

void board::board_save(int save_mode) // saves the board
{
	ofstream seq_fileOut;

	seq_fileIn.open("sequenceFile.txt", ios::in);

	if (seq_fileIn.is_open()) // automatically numbers every saved board
	{
		seq_fileIn >> file_seq;
		file_seq++;
	}
	else
		file_seq = 1; 

	seq_fileOut.open("sequenceFile.txt", ios::out);
	seq_fileOut << file_seq;
	seq_fileOut.close();

	string filename;
	
	if (file_seq < 100 && file_seq > 9)
		filename = "b" + to_string(0) +to_string(file_seq) + ".txt";
	else if (file_seq < 1000 && file_seq > 99)
		filename = "b" + to_string(file_seq) + ".txt";
	else filename = "b" + to_string(0) + to_string(0) + to_string(file_seq) + ".txt";

	cout << "This board's name is " << filename << endl;

	save_file.open(filename);

	save_file << l << endl << c << endl << save_mode << endl;

	for (unsigned int i = 0; i < board_words.size(); i++)
	{
		save_file << board_words.at(i) << " ";
	}

	save_file << endl;

	for (unsigned int i = 0; i < posit.size(); i++)
	{
		save_file << posit.at(i) << " ";
	}

	save_file << endl;

	for (unsigned int i = 0; i < l; i++)
	{
		for (unsigned int j = 0; j < c; j++)
		{
			save_file << board_contents.at(i).at(j);
		}

		save_file << endl;
	}
	save_file << endl;
	system("pause");
}

void board::board_remove() // removes a word from the board
{
	for (unsigned int i = 0; i < posit.size(); i++)
	{
		if (position == posit.at(i))
		{
			posit.erase(posit.begin() + i);
			board_words.erase(board_words.begin() + i);

			for (unsigned int i = 0; i <= l; i++) 
			{
				for (unsigned int j = 0; j <= c; j++)
				{
					board_contents.at(i).at(j) = '.';
				}
			}

			for (unsigned int i = 0; i < posit.size(); i++) // rebuilds the board without the removed word after resetting the board
			{
				string repos = posit.at(i);
				string reword = board_words.at(i);

				char line = repos[0];
				char column = repos[1];
				char direction = repos[2];

				if (direction == 'V')
				{
					for (unsigned int i = 0; i <= reword.length(); i++)
					{
						board_contents[int(line) - 65 + i][int(column) - 97] = reword[i];
						if ((int(line) - 65 - 1) != -1)
							board_contents[int(line) - 65 - 1][int(column) - 97] = '#';
						if ((int(line) - 65 - 1) != (int(line) + 1))
							board_contents[int(line) - 65 + reword.length()][int(column) - 97] = '#';
					}
				}
				else if (direction == 'H')
				{
					for (unsigned int i = 0; i <= reword.length(); i++)
					{
						board_contents[int(line) - 65][int(column) - 97 + i] = reword[i];
						if ((int(column) - 97 - 1) != -1)
							board_contents[int(line) - 65][int(column) - 97 - 1] = '#';
						if ((int(column) - 97 - 1) != (int(column) + 1))
							board_contents[int(line) - 65][int(column) - 97 + reword.length()] = '#';
					}
				}
			}
		}
	}
}