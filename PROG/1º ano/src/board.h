#ifndef board_H
#define board_H
#include <vector>
#include <string>
#include <fstream>
#include "dictionary.h"

class board
{
	friend class dictionary;
public:
	board();
	board(int nlin, int ncol);
	bool board_valid(dictionary &dic);
	void board_input(dictionary &dic);
	void board_display();
	void board_load();
	void board_save(int save_mode);
	void board_remove();
private:
	unsigned int c; // board size (columns)
	unsigned int l; // board size (lines)
	vector < vector <char> > board_contents; // contains the board elements (letters, dots, black cells)
	string position; // Line/Column/Direction input
	string word; // word input
	vector <string> board_words; // store the words that are currently in the puzzle
	vector <string> posit; // store the positions of the word that are currently in the puzzle
	ofstream save_file; 
	ifstream load_file;
	unsigned int file_seq; // used to save boards of incrementing numbers
	ifstream seq_fileIn; // save file_seq in a file
};

#endif

