#include "stdafx.h"
#include "Lab4.h"
#include "gameBase.h"
#include "TicTacToe.h"
#include "Gomoku.h"
#include "Sudoku.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <iomanip>
#include <memory>

using namespace std;

//--------------------------------------------------------------------
// gamePiece

gamePiece::gamePiece(string a) {
	display = a;
	size = a.size();

}
gamePiece::gamePiece(unsigned int anInt) {
	string a = to_string(anInt);
	
	display = a;
	size = a.size();

}
//--------------------------------------------------------------------
//gameBase

shared_ptr<gameBase> gameBase::ptr = nullptr;

//constructor
gameBase::gameBase() {
	width = 5; height = 5; longestDisp = 0; 
	gamePiece t(" ");
	for (int i = 1; i <= width*height;++i) {		//push back spaces
		pieceVector.push_back(t);
	}	
}

//instance method
shared_ptr<gameBase> gameBase::instance() {
	if (ptr == nullptr) {				
		//throw exception
		try
		{
			throw NULL_PTR_EXCEPTION;
		}
		catch(failures NULL_PTR_EXCEPTION)
		{
			int a = NULL_PTR_EXCEPTION;		//included to get rid of warning
			return ptr;
		}		
	}
	else {
		return ptr;
	}
}

//prompts user to enter coordinate of a square or "quit"
int gameBase::prompt(int &horizontal, int &vertical) {
	cout << "please enter a coordinate pair (e.g. '1,1') or 'quit' to end the game." << endl;

	string input;
	getline(cin, input);
	lowerMaker(input);
	if (input == "quit") {
		//user quits
		cout << "You have ended the game after " << turns <<" turns."<< endl <<"Would you like to save your current game? (yes/no)" << endl;
		string saveOrNot;
		while (saveOrNot != "yes" && saveOrNot != "no") {
			cout << "Please type 'yes' to save or 'no' to not save your game." << endl;			//checks if poorly formated response
			cin >> saveOrNot;
			lowerMaker(saveOrNot);
		}
		if (saveOrNot == "yes") {		//saves game
			return QUIT_SAVE;
		}
		else if (saveOrNot == "no") {	//save file is just "NODATA"
			return QUIT_NO_SAVE;
		}
	}
	else {
		//now change commas to spaces

		for (unsigned int i = 0;i < input.size();i++) {
			if (input[i] == ',') {
				input[i] = ' ';
			}
		}
		istringstream stream(input);
		if (width > 5 && height > 5) {
			realWidth = 19; realHeight = 19;
		}
		else {
			realWidth = 3; realHeight = 3;
		}
		if (stream >> horizontal >> vertical) {
			if (horizontal < 1 || horizontal > realWidth || vertical < 1 || vertical > realHeight) { //checks if inputs in range
				cout << "Please enter coordinates with values from 1 to " << realHeight << endl;
				validPiece = false;
				playerX = !playerX;
				return BAD_PIECE;
			}
			else {
				validPiece = true;
				return GOOD_PIECE;
			}
		}
		else {																					//checks if good inputs
			cout << "Make sure to use form 'x,y' for coordinates" << endl;
			validPiece = false;
			playerX = !playerX;
			return BAD_PIECE;
		}
	}
	return SUCCESS;
}

int gameBase::play() {
	print();
	int x = 0;
	
	while (!done() && !draw() && !isFinished) {
		x = turn();
		if (x == QUIT_SAVE || x == QUIT_NO_SAVE) {
			return x;
		}
	}
	if (done()) {																											//game is won
		if (isSudoku) {
			cout << endl << "Congratulations, " << currentDisp << "you have won!" << endl;			//sudoku win
		}
		else {																						//tictactoe/gomoku win
			cout << endl << "Congratulations player " << currentDisp << ", you have won!" << endl << "Turns: " << turns << endl;
		}
		if (currentDisp == "X") {
			return SUCCESS;
		}
		else {
			return SUCCESS;
		}
	}
	if (x == QUIT_SAVE || x == QUIT_NO_SAVE) {
		return x;
	}
	return x;
}

//baseargs
void gameBase::baseArgs(int argc, char* argv[]) {
	gameBase* game;
	if (ptr != nullptr) {
		//throw exception
			throw NOT_NULL;
	}
	else {
		//allocates game object 
		if (argc == 2) {
			if (strcmp(argv[1], "TicTacToe") == 0) {
				try {
					//game = new TicTacToe();
					ptr = make_shared<TicTacToe>();
				}
				catch (failures e) {																		//catching exceptions
					cout << "bad_alloc exception for TicTacToe game. Exception: " << e << endl;
				}
			}
			else if (strcmp(argv[1], "Gomoku") == 0) {
				try {
					ptr = make_shared<Gomoku>();
				}
				catch (failures e) {
					cout << "bad_alloc exception for Gomoku game. Exception: " << e << endl;
				}
			}
			else if (strcmp(argv[1], "Sudoku") == 0) {
				try {
					ptr = make_shared<Sudoku>();
				}
				catch (failures e) {
					cout << "bad_alloc exception for Sudoku game. Exception: " << e << endl;
				}
			}
			else {
				//No object was constructed! Returns nullptr
				game = nullptr;
				//throw exception
				try {
					throw BAD_GAME_NAME;
				}
				catch (failures e) {
					cout << "Bad game name; please enter valid game name. Exception: " << e << endl;
				}
			}
		}
		else {
			game = nullptr;
			//throw exception
			try {
				throw TOO_MANY_ARGS;
			}
			catch (failures e) {
				cout << "Too many arguments. Exception: " << e << endl;
			}
		}
	}
	
}

void gameBase::updateLongest(int a) {
	longestDisp = a;
}
