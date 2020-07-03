#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <array>
#include <iostream>
#include "q_learning.h"
#include "sarsa.h"

#ifdef _WIN32
#include <windows.h>

void sleep(unsigned milliseconds)
{
	Sleep(milliseconds);
}
#else
#include <unistd.h>

void sleep(unsigned milliseconds)
{
	usleep(milliseconds * 1000);
}
#endif


using namespace std;

#define HEI 8
#define WID 8
#define UNIFORM_PUSH_WEIGHT 1 // Define how heavily the uniform_cost_search should value box pushes. 0: Box pushes don't matter, only movements. 1: Pushes worth same as movements.

using namespace std;

struct GridLocation { // Position of an item on the board
	int x, y;
};

struct gamePositions { // Combined positions of all items on the board
	GridLocation player;
	GridLocation exit;
	vector<GridLocation> boxes;
};

bool operator == (GridLocation a, GridLocation b) { // Check if two items are in the same place
	if (a.x == b.x && a.y == b.y) return true;
	else return false;
}

bool operator == (gamePositions a, gamePositions b) { // Check if the combined positions of two game states are equal
	if (a.player == b.player) {
		if (a.boxes.size() == b.boxes.size()) {
			for (int i = 0; i < a.boxes.size(); i++) {
				if (!(a.boxes.at(i) == b.boxes.at(i))) {
					return false;
				}
			}
			return true;
		}
		else return false;
	}
	else return false;
}

struct state {
	char board[HEI][WID]; // Array containing all board items
	vector<string> movelist; // List of moves used to get to the game state
	int nmoves; // Number of times the player has moved 
	int npushes; // Number of times the player has pushed a box
	gamePositions positions; // Combined positions of all items
	bool isWon = false; // Flag to check if the level has been beated
};

// List of all the levels to play in the game:

// Positions:
//'J' -> Player
//'S' -> Exit
//'C' -> Box
//'P' -> Wall
//'_' -> Empty Space

char level1[8][8] = { {'P','P','P','P','P','P','P','P'},
					{'P','_','_','_','_','_','_','P'},
					{'P','_','J','_','_','_','_','P'},
					{'P','_','_','_','_','_','_','P'},
					{'P','P','P','_','_','_','_','P'},
					{'P','_','_','_','_','_','_','S'},
					{'P','_','_','_','_','_','_','P'},
					{'P','P','P','P','P','P','P','P'} };

char level2[8][8] = { {'P','P','P','P','P','P','P','P'},
					{'P','P','P','P','P','P','P','P'},
					{'P','P','_','_','_','P','P','P'},
					{'P','P','_','P','_','P','P','P'},
					{'P','_','_','P','_','P','P','P'},
					{'P','J','P','_','_','P','P','P'},
					{'P','P','P','S','P','P','P','P'},
					{'P','P','P','P','P','P','P','P'} };

char level3[8][8] = { {'P','P','P','P','P','P','P','P'},
					{'P','P','P','P','_','P','P','P'},
					{'P','J','_','_','_','_','_','P'},
					{'P','P','P','_','_','P','_','P'},
					{'P','P','P','P','P','S','_','P'},
					{'P','P','P','P','P','P','_','P'},
					{'P','P','P','P','P','P','P','P'},
					{'P','P','P','P','P','P','P','P'} };

char level4[8][8] = { {'P','P','P','P','P','P','P','P'},
					{'P','P','P','S','P','P','P','P'},
					{'P','P','_','_','_','_','P','P'},
					{'P','P','_','_','_','_','P','P'},
					{'P','P','_','_','_','_','P','P'},
					{'P','P','_','J','_','_','P','P'},
					{'P','P','P','P','P','P','P','P'},
					{'P','P','P','P','P','P','P','P'} };

char level5[8][8] = { {'P','P','P','P','P','P','P','P'},
					{'P','P','P','P','P','P','P','P'},
					{'P','_','P','_','_','_','_','P'},
					{'S','_','P','_','_','P','J','P'},
					{'P','_','_','_','_','_','_','P'},
					{'P','P','P','P','P','P','P','P'},
					{'P','P','P','P','P','P','P','P'},
					{'P','P','P','P','P','P','P','P'} };

char level6[8][8] = { {'P','P','P','P','P','P','P','P'},
					{'P','_','_','_','_','_','_','P'},
					{'P','_','J','_','_','_','_','P'},
					{'P','_','_','P','P','_','P','P'},
					{'P','_','_','_','P','_','P','P'},
					{'P','_','_','_','P','_','_','S'},
					{'P','_','_','_','_','_','_','P'},
					{'P','P','P','P','P','P','P','P'} };

char level7[8][8] = { {'P','P','P','P','P','P','P','P'},
					{'P','_','P','_','_','_','_','P'},
					{'P','_','P','_','_','P','_','P'},
					{'S','_','P','_','_','P','J','P'},
					{'P','_','P','_','P','P','_','P'},
					{'P','_','_','_','_','_','_','P'},
					{'P','_','_','_','P','P','_','P'},
					{'P','P','P','P','P','P','P','P'} };

double newR[64][64];
void initialR(q_learning* test);
void buildRMatrix(state* gB, q_learning* test);
void initialR(sarsa* test);
void buildRMatrix(state* gB, sarsa* test);
void print_matrix(double m[64][64]);
void loadBoxPositions(state* gB);
int initState(state* gB, int level);
void drawState(state gB);
int makeMove(state* gB, string direction);
bool checkValidMove(state* gB, string direction);
int doValidMove(state* gB, string direction);
int pushBox(state* gB, string direction);
int getWin(state* gB);

void initialR(q_learning* test) { // initialize the R matrix
	int count = 0;
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64; j++) {
			newR[i][j] = -1;
			count++;
		}
	}
	test->setR(newR);
}

void initialR(sarsa* test) { // initialize the R matrix
	int count = 0;
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64; j++) {
			newR[i][j] = -1;
			count++;
		}
	}
	test->setR(newR);
}

void buildRMatrix(state* gB, q_learning* test) { // put valid moves in the R matrix and send it to the q_learning class
	GridLocation savePlayerPosition = gB->positions.player;
	for (int i = 0; i < 64; i++) {
		int x = i % 8;
		int y = i / 8;
		if (gB->board[y][x] == 'P')
			continue;
		else if (gB->board[y][x] == 'S')
			continue;
		else {
			gB->positions.player.x = x;
			gB->positions.player.y = y;
			if (y > 0) {
				if (checkValidMove(gB, "Up") == 1) {
					if (gB->positions.exit.x == x && gB->positions.exit.y == y - 1)
						newR[i][i - 8] = 100;
					else
						newR[i][i - 8] = 0;
				}
				else
					newR[i][i - 8] = -1;
			}
			if (y < 7) {
				if (checkValidMove(gB, "Down") == 1) {
					if (gB->positions.exit.x == x && gB->positions.exit.y == y + 1)
						newR[i][i + 8] = 100;
					else
						newR[i][i + 8] = 0;
				}
				else
					newR[i][i + 8] = -1;
			}
			if (x > 0) {
				if (checkValidMove(gB, "Left") == 1) {
					if (gB->positions.exit.x == x - 1 && gB->positions.exit.y == y)
						newR[i][i - 1] = 100;
					else
						newR[i][i - 1] = 0;
				}
				else
					newR[i][i - 1] = -1;
			}
			if (x < 7) {
				if (checkValidMove(gB, "Right") == 1) {
					if (gB->positions.exit.x == x + 1 && gB->positions.exit.y == y)
						newR[i][i + 1] = 100;
					else
						newR[i][i + 1] = 0;
				}
				else
					newR[i][i + 1] = -1;
			}
		}
	}
	gB->positions.player = savePlayerPosition;
	test->setR(newR);
}

void buildRMatrix(state* gB, sarsa* test) { // put valid moves in the R matrix and send it to the sarsa class
	GridLocation savePlayerPosition = gB->positions.player;
	for (int i = 0; i < 64; i++) {
		int x = i % 8;
		int y = i / 8;
		if (gB->board[y][x] == 'P')
			continue;
		else if (gB->board[y][x] == 'S') {
			newR[i][i] = 100;
			continue;
		}
		else {
			gB->positions.player.x = x;
			gB->positions.player.y = y;
			if (y > 0) {
				if (checkValidMove(gB, "Up") == 1) {
					if (gB->positions.exit.x == x && gB->positions.exit.y == y - 1)
						newR[i][i - 8] = 100;
					else
						newR[i][i - 8] = 0;
				}
				else
					newR[i][i - 8] = -1;
			}
			if (y < 7) {
				if (checkValidMove(gB, "Down") == 1) {
					if (gB->positions.exit.x == x && gB->positions.exit.y == y + 1)
						newR[i][i + 8] = 100;
					else
						newR[i][i + 8] = 0;
				}
				else
					newR[i][i + 8] = -1;
			}
			if (x > 0) {
				if (checkValidMove(gB, "Left") == 1) {
					if (gB->positions.exit.x == x - 1 && gB->positions.exit.y == y)
						newR[i][i - 1] = 100;
					else
						newR[i][i - 1] = 0;
				}
				else
					newR[i][i - 1] = -1;
			}
			if (x < 7) {
				if (checkValidMove(gB, "Right") == 1) {
					if (gB->positions.exit.x == x + 1 && gB->positions.exit.y == y)
						newR[i][i + 1] = 100;
					else
						newR[i][i + 1] = 0;
				}
				else
					newR[i][i + 1] = -1;
			}
		}
	}
	gB->positions.player = savePlayerPosition;
	test->setR(newR);
}

void print_matrix(double m[64][64]) { // print the valid moves on the R matrix only
	for (int i = 0; i < 64; ++i) {
		int x = i % 8;
		int y = i / 8;
		cout << "State (" << x << ", " << y << ") ";
		if (x > 0)
			cout << "Left: " << m[i][i - 1] << " ";
		if (x < 7)
			cout << "Right: " << m[i][i + 1] << " ";
		if (y > 0)
			cout << "Up: " << m[i][i - 8] << " ";
		if (y < 7)
			cout << "Down: " << m[i][i + 8] << " ";
		cout << endl;
	}
}

int menuValidInput(string message, int min, int max) { // Restrict input on the menu, only allow input for the given numbered options
	bool valid = false;
	int input;
	cout << message;
	cin >> input;
	if (cin.fail() || (input < min || input > max)) {
		cin.clear();
		cin.ignore(1000, '\n');
	}
	else
		valid = true;
	while (!valid) {
		cout << "Invalid value, choose between " << min << " and " << max << "." << endl;
		cout << message;
		cin >> input;
		if (cin.fail() || (input < min || input > max)) {
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else
			valid = true;
	}
	cin.ignore(1000, '\n');
	return input;
}

int main() {
	while (1) {
		cout << endl << "========== BOXWORLD ==========" << endl << endl;
		cout << "(1) - Play the game" << endl;
		cout << "(2) - Start the machine learning process" << endl;
		cout << "(3) - Exit" << endl << endl;
		int option = menuValidInput("Option:", 1, 3);
		if (option == 1) {
			int level = 1;
			state gameBoard;
			initState(&gameBoard, level);
			string key;
			bool gameOver = false;
			while (gameOver == false) {
				drawState(gameBoard);
				cout << "Current Player Position: " << gameBoard.positions.player.x << "," << gameBoard.positions.player.y << " (R to restart level, Q to quit game)" << endl;
				cout << "Introduce direction you want to move in: 'W' for 'Up', 'S' for 'Down', 'A' for 'Left', 'D' for 'Right'" << endl;
				cin >> key;
				if (key == "W" || key == "w") doValidMove(&gameBoard, "Up");
				else if (key == "S" || key == "s") doValidMove(&gameBoard, "Down");
				else if (key == "A" || key == "a") doValidMove(&gameBoard, "Left");
				else if (key == "D" || key == "d") doValidMove(&gameBoard, "Right");
				else if (key == "R" || key == "r") initState(&gameBoard, level);
				else if (key == "Q" || key == "q") break;
				else cout << "Invalid key, please try again" << endl;
				if (gameBoard.isWon == true) {
					drawState(gameBoard);
					cout << "Congratulations, you won! You took " << gameBoard.nmoves << " steps and pushed boxes " << gameBoard.npushes << " times, earning a score of " << (UNIFORM_PUSH_WEIGHT * gameBoard.npushes) + gameBoard.nmoves << "!" << endl;
					level++;
					if (level == 8) {
						cout << "You have beaten the game!" << endl;
						gameOver = true;
					}
					else
						initState(&gameBoard, level);
				}
			}
		}
		else if (option == 2) {
			cout << "Choose your algorithm:" << endl;
			cout << "(1) - Q-Learning" << endl;
			cout << "(2) - SARSA" << endl;
			int second_option = menuValidInput("Option:", 1, 2);
			if (second_option == 1) {
				cout << "How many episodes do you wish to run per level?" << endl;
				int episodes = menuValidInput("Episodes:", 25, 10000);
				for (int level = 1; level < 8; level++) {
					cout << endl;
					cout << "Level " << level << ":";
					for (int a = 0; a < 10; a++) {
						state gameBoard;
						initState(&gameBoard, level);
						int startingState = gameBoard.positions.player.x + (gameBoard.positions.player.y * 8);
						int goalState = gameBoard.positions.exit.x + (gameBoard.positions.exit.y * 8);
						q_learning test(goalState, episodes, 2);
						initialR(&test);
						buildRMatrix(&gameBoard, &test);
						test.run_training(startingState);
						//sleep(500);
						bool gameOver = false;
						int currentState = startingState;
						//drawState(gameBoard);
						while (gameOver == false) {
							int nextState = test.retrieve_best_action(currentState);
							string move = "";
							if ((nextState - currentState) == 1) {
								move = "Right";
							}
							else if ((nextState - currentState) == -1) {
								move = "Left";
							}
							else if ((nextState - currentState) == 8) {
								move = "Down";
							}
							else if ((nextState - currentState) == -8) {
								move = "Up";
							}
							else {
								cout << "fail \ ";
								break;
							}
							//sleep(650);
							doValidMove(&gameBoard, move);
							//drawState(gameBoard);
							currentState = nextState;
							if (gameBoard.isWon == true) {
								cout << gameBoard.nmoves << " \ ";
								//cout << "Congratulations, you beat level " << level << "! You took " << gameBoard.nmoves << " steps and pushed boxes " << gameBoard.npushes << " times, earning a score of " << (UNIFORM_PUSH_WEIGHT * gameBoard.npushes) + gameBoard.nmoves << "!" << endl;
								if (level == 7) {
									//cout << "You have beaten the game!" << endl;
									gameOver = true;
								}
								else
									break;
							}
						}
					}
				}
			}
			else if (second_option == 2) {
				cout << "How many episodes do you wish to run per level?" << endl;
				int episodes = menuValidInput("Episodes:", 25, 10000);
				for (int level = 1; level < 8; level++) {
					cout << endl;
					cout << "Level " << level << ":";
					for (int a = 0; a < 10; a++) {
						state gameBoard;
						initState(&gameBoard, level);
						int startingState = gameBoard.positions.player.x + (gameBoard.positions.player.y * 8);
						int goalState = gameBoard.positions.exit.x + (gameBoard.positions.exit.y * 8);
						sarsa test(goalState, episodes, 2);
						initialR(&test);
						buildRMatrix(&gameBoard, &test);
						test.run_training(startingState);
						//sleep(500);
						bool gameOver = false;
						int currentState = startingState;
						//drawState(gameBoard);
						int count = 0;
						while (gameOver == false) {
							count++;
							if (count > 300) {
								cout << "stuck \ ";
								break;
							}
							int nextState = test.retrieve_best_action(currentState);
							string move = "";
							if ((nextState - currentState) == 1) {
								move = "Right";
							}
							else if ((nextState - currentState) == -1) {
								move = "Left";
							}
							else if ((nextState - currentState) == 8) {
								move = "Down";
							}
							else if ((nextState - currentState) == -8) {
								move = "Up";
							}
							else {
								cout << "fail \ ";
								break;
							}
							//sleep(650);
							doValidMove(&gameBoard, move);
							//drawState(gameBoard);
							currentState = nextState;
							if (gameBoard.isWon == true) {
								cout << gameBoard.nmoves << " \ ";
								//cout << "Congratulations, you beat level " << level << "! You took " << gameBoard.nmoves << " steps and pushed boxes " << gameBoard.npushes << " times, earning a score of " << (UNIFORM_PUSH_WEIGHT * gameBoard.npushes) + gameBoard.nmoves << "!" << endl;
								if (level == 7) {
									//cout << "You have beaten the game!" << endl;
									gameOver = true;
								}
								else
									break;
							}
						}
					}
				}
			}
		}
		else if (option == 3)
			return 0;
	}
}

void loadBoxPositions(state* gB) { // Fill the combined positions field with the box positions
	gB->positions.boxes.clear();
	for (int i = 0; i < HEI; i++) {
		for (int j = 0; j < WID; j++) {
			if (gB->board[i][j] == 'C') {
				GridLocation box;
				box.x = j;
				box.y = i;
				gB->positions.boxes.push_back(box);
			}
		}
	}
}

int initState(state* gB, int level) { // Initialize the given level with the starting state
	if (HEI < 1) return 1;
	if (WID < 1) return 1;

	for (int i = 0; i < HEI; i++) {
		for (int j = 0; j < WID; j++) {
			if (level == 1)
				gB->board[i][j] = level1[i][j];
			else if (level == 2)
				gB->board[i][j] = level2[i][j];
			else if (level == 3)
				gB->board[i][j] = level3[i][j];
			else if (level == 4)
				gB->board[i][j] = level4[i][j];
			else if (level == 5)
				gB->board[i][j] = level5[i][j];
			else if (level == 6)
				gB->board[i][j] = level6[i][j];
			else if (level == 7)
				gB->board[i][j] = level7[i][j];
		}
	}
	gB->nmoves = 0;
	gB->npushes = 0;
	gB->movelist.clear();
	gB->isWon = false;
	if (level == 1) {
		gB->positions.player.x = 2;
		gB->positions.player.y = 2;
		gB->positions.exit.x = 7;
		gB->positions.exit.y = 5;
	}
	else if (level == 2) {
		gB->positions.player.x = 1;
		gB->positions.player.y = 5;
		gB->positions.exit.x = 3;
		gB->positions.exit.y = 6;
	}
	else if (level == 3) {
		gB->positions.player.x = 1;
		gB->positions.player.y = 2;
		gB->positions.exit.x = 5;
		gB->positions.exit.y = 4;
	}
	else if (level == 4) {
		gB->positions.player.x = 3;
		gB->positions.player.y = 5;
		gB->positions.exit.x = 3;
		gB->positions.exit.y = 1;
	}
	else if (level == 5) {
		gB->positions.player.x = 6;
		gB->positions.player.y = 3;
		gB->positions.exit.x = 0;
		gB->positions.exit.y = 3;
	}
	else if (level == 6) {
		gB->positions.player.x = 2;
		gB->positions.player.y = 2;
		gB->positions.exit.x = 7;
		gB->positions.exit.y = 5;
	}
	else if (level == 7) {
		gB->positions.player.x = 6;
		gB->positions.player.y = 3;
		gB->positions.exit.x = 0;
		gB->positions.exit.y = 3;
	}
	loadBoxPositions(gB);
	return 0;
}

void drawState(state gB) { // Draws the current game state's board on the screen
	cout << endl;
	for (int y = 0; y < HEI; y++) {
		cout << endl;
		for (int x = 0; x < WID; x++) {
			cout << "|";
			cout << gB.board[y][x];
		}
	}
	cout << endl;
}

bool checkValidMove(state* gB, string direction) { // Check if a move in a given direction is valid. Returns 1 if the move is valid, 0 if not
	if (direction == "Up") {
		if (gB->positions.player.y - 1 < 0) return 0;
		else if (gB->board[gB->positions.player.y - 1][gB->positions.player.x] == '_') return 1;
		else if (gB->board[gB->positions.player.y - 1][gB->positions.player.x] == 'C') {
			if (gB->board[gB->positions.player.y - 2][gB->positions.player.x] == '_') { return 1; }
			else return 0;
		}
		else if (gB->board[gB->positions.player.y - 1][gB->positions.player.x] == 'P') return 0;
		else if (gB->board[gB->positions.player.y - 1][gB->positions.player.x] == 'S') { return 1; }
	}
	else if (direction == "Down") {
		if (gB->positions.player.y + 1 > HEI) return 0;
		else if (gB->board[gB->positions.player.y + 1][gB->positions.player.x] == '_') return 1;
		else if (gB->board[gB->positions.player.y + 1][gB->positions.player.x] == 'C') {
			if (gB->board[gB->positions.player.y + 2][gB->positions.player.x] == '_') { return 1; }
			else return 0;
		}
		else if (gB->board[gB->positions.player.y + 1][gB->positions.player.x] == 'P') return 0;
		else if (gB->board[gB->positions.player.y + 1][gB->positions.player.x] == 'S') { return 1; }
	}
	else if (direction == "Left") {
		if (gB->positions.player.x - 1 < 0) return 0;
		else if (gB->board[gB->positions.player.y][gB->positions.player.x - 1] == '_') return 1;
		else if (gB->board[gB->positions.player.y][gB->positions.player.x - 1] == 'C') {
			if (gB->board[gB->positions.player.y][gB->positions.player.x - 2] == '_') { return 1; }
			else return 0;
		}
		else if (gB->board[gB->positions.player.y][gB->positions.player.x - 1] == 'P') return 0;
		else if (gB->board[gB->positions.player.y][gB->positions.player.x - 1] == 'S') { return 1; }
	}
	else if (direction == "Right") {
		if (gB->positions.player.x + 1 > WID) return 0;
		else if (gB->board[gB->positions.player.y][gB->positions.player.x + 1] == '_') return 1;
		else if (gB->board[gB->positions.player.y][gB->positions.player.x + 1] == 'C') {
			if (gB->board[gB->positions.player.y][gB->positions.player.x + 2] == '_') { return 1; }
			else return 0;
		}
		else if (gB->board[gB->positions.player.y][gB->positions.player.x + 1] == 'P') return 0;
		else if (gB->board[gB->positions.player.y][gB->positions.player.x + 1] == 'S') { return 1; }
	}
	return 0;
}

int doValidMove(state* gB, string direction) { // Check if a move in a given direction is valid, and if so, execute it. Returns 0 if the move is successful, otherwise 1
	if (direction == "Up") {
		if (gB->positions.player.y - 1 < 0) return 1;
		else if (gB->board[gB->positions.player.y - 1][gB->positions.player.x] == '_') makeMove(gB, direction);
		else if (gB->board[gB->positions.player.y - 1][gB->positions.player.x] == 'C') {
			if (gB->board[gB->positions.player.y - 2][gB->positions.player.x] == '_') { pushBox(gB, direction); makeMove(gB, direction); }
			else return 1;
		}
		else if (gB->board[gB->positions.player.y - 1][gB->positions.player.x] == 'P') return 1;
		else if (gB->board[gB->positions.player.y - 1][gB->positions.player.x] == 'S') { makeMove(gB, direction); getWin(gB); }
	}
	else if (direction == "Down") {
		if (gB->positions.player.y + 1 > HEI) return 1;
		else if (gB->board[gB->positions.player.y + 1][gB->positions.player.x] == '_') makeMove(gB, direction);
		else if (gB->board[gB->positions.player.y + 1][gB->positions.player.x] == 'C') {
			if (gB->board[gB->positions.player.y + 2][gB->positions.player.x] == '_') { pushBox(gB, direction); makeMove(gB, direction); }
			else return 1;
		}
		else if (gB->board[gB->positions.player.y + 1][gB->positions.player.x] == 'P') return 1;
		else if (gB->board[gB->positions.player.y + 1][gB->positions.player.x] == 'S') { makeMove(gB, direction); getWin(gB); }
	}
	else if (direction == "Left") {
		if (gB->positions.player.x - 1 < 0) return 1;
		else if (gB->board[gB->positions.player.y][gB->positions.player.x - 1] == '_') makeMove(gB, direction);
		else if (gB->board[gB->positions.player.y][gB->positions.player.x - 1] == 'C') {
			if (gB->board[gB->positions.player.y][gB->positions.player.x - 2] == '_') { pushBox(gB, direction); makeMove(gB, direction); }
			else return 1;
		}
		else if (gB->board[gB->positions.player.y][gB->positions.player.x - 1] == 'P') return 1;
		else if (gB->board[gB->positions.player.y][gB->positions.player.x - 1] == 'S') { makeMove(gB, direction); getWin(gB); }
	}
	else if (direction == "Right") {
		if (gB->positions.player.x + 1 > WID) return 1;
		else if (gB->board[gB->positions.player.y][gB->positions.player.x + 1] == '_') makeMove(gB, direction);
		else if (gB->board[gB->positions.player.y][gB->positions.player.x + 1] == 'C') {
			if (gB->board[gB->positions.player.y][gB->positions.player.x + 2] == '_') { pushBox(gB, direction); makeMove(gB, direction); }
			else return 1;
		}
		else if (gB->board[gB->positions.player.y][gB->positions.player.x + 1] == 'P') return 1;
		else if (gB->board[gB->positions.player.y][gB->positions.player.x + 1] == 'S') { makeMove(gB, direction); getWin(gB); }
	}
	return 0;
}


int pushBox(state* gB, string direction) { // Push a box and save it on the game state
	gB->npushes++;
	if (direction == "Up") {
		gB->board[gB->positions.player.y - 1][gB->positions.player.x] = '_';
		gB->board[gB->positions.player.y - 2][gB->positions.player.x] = 'C';
	}
	else if (direction == "Down") {
		gB->board[gB->positions.player.y + 1][gB->positions.player.x] = '_';
		gB->board[gB->positions.player.y + 2][gB->positions.player.x] = 'C';
	}
	else if (direction == "Left") {
		gB->board[gB->positions.player.y][gB->positions.player.x - 1] = '_';
		gB->board[gB->positions.player.y][gB->positions.player.x - 2] = 'C';
	}
	else if (direction == "Right") {
		gB->board[gB->positions.player.y][gB->positions.player.x + 1] = '_';
		gB->board[gB->positions.player.y][gB->positions.player.x + 2] = 'C';
	}
	loadBoxPositions(gB);
	return 0;
}

int makeMove(state* gB, string direction) { // Execute a move and save it on the game state
	gB->nmoves++;
	gB->movelist.push_back(direction);
	gB->board[gB->positions.player.y][gB->positions.player.x] = '_';
	if (direction == "Up") {
		gB->positions.player.y--;
	}
	else if (direction == "Down") {
		gB->positions.player.y++;
	}
	else if (direction == "Left") {
		gB->positions.player.x--;
	}
	else if (direction == "Right") {
		gB->positions.player.x++;
	}
	gB->board[gB->positions.player.y][gB->positions.player.x] = 'J';
	return 0;
}

int getWin(state* gB) { // Level over, make the player win on the next frame
	gB->isWon = true;
	return 0;
}

