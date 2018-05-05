#include "stdafx.h"
#include "Lab4.h"
#include "gameBase.h"
#include "TicTacToe.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <iomanip>

//--------------------------------------------------------------------
//TicTacToe

//constructor
TicTacToe::TicTacToe() {
	width = 5; height = 5; longestDisp = 0; realWidth = 3; realHeight = 3;turns = 0;
	ifstream ifs("tictactoe.txt");
	if (ifs.is_open()) {
		string s;
		ifs >> s;
		gamePiece t(" ");
		for (int i = 1; i <= width*height;++i) {
			pieceVector.push_back(t);
		}
		if (s == "NODATA") {
			//nothing to read 
		}
		else if (s == "tictactoe") {
			// load previously saved game
			ifstream ifs;
			ifs.open("tictactoe.txt");
			string aString;
			string string2;
			if (ifs.is_open()) {
				getline(ifs, string2);
				getline(ifs, string2);
				istringstream is1(string2);
				is1 >> currentDisp ;
					
				inputDisp = "X";
				turns = 0;
				while (getline(ifs,aString)) {
					if (aString[0] == ' ') {
						break;
					}
						
					istringstream iss(aString);
					int vert; int hor;
					iss >> hor >> vert;
					if (hor > 0 && pieceVector[(vert + 1) * 5 - hor - 1].display == " ") {
							
						pieceVector[(vert + 1) * 5 - hor - 1].display = inputDisp;
						moveArray[turns][0] = hor;
						moveArray[turns][1] = vert;
						turns++;
						if (inputDisp == "X") {
							inputDisp = "O";
							playerX = !playerX;
						}
						else if (inputDisp == "O") {
							inputDisp = "X";
							playerX = !playerX;
						}
					}		
				}
								
				ifs.close();
			}
			else {
				cout << "Unable to open file stream" << endl;
			}
		}
		else {
			cout << "Improperly formatted file (first_line)" << endl;
		}
	}
}

//returns true if game has been won
bool TicTacToe::done() {
	if (pieceVector[A1].display == pieceVector[A2].display && pieceVector[A2].display == pieceVector[A3].display && pieceVector[A3].display != " "
		|| pieceVector[B1].display == pieceVector[B2].display && pieceVector[B2].display == pieceVector[B3].display && pieceVector[B3].display != " "
		|| pieceVector[C1].display == pieceVector[C2].display && pieceVector[C2].display == pieceVector[C3].display && pieceVector[C3].display != " "
		|| pieceVector[A1].display == pieceVector[B1].display && pieceVector[B1].display == pieceVector[C1].display && pieceVector[C1].display != " "
		|| pieceVector[A2].display == pieceVector[B2].display && pieceVector[B2].display == pieceVector[C2].display && pieceVector[C2].display != " "
		|| pieceVector[A3].display == pieceVector[B3].display && pieceVector[B3].display == pieceVector[C3].display && pieceVector[C3].display != " "
		|| pieceVector[A1].display == pieceVector[B2].display && pieceVector[B2].display == pieceVector[C3].display && pieceVector[C3].display != " "
		|| pieceVector[A3].display == pieceVector[B2].display && pieceVector[B2].display == pieceVector[C1].display && pieceVector[C1].display != " ") {
		//winning condition, rewrite file to NODATA
		ofstream ofs("tictactoe.txt", ofstream::out);
		ofs << "NODATA";
		ofs.close();
		return true;
	}
	else {
		return false;
	}
}

//returns false if no moves remaining or if done() returns true
bool TicTacToe::draw() {
	if (done()) {
		return false;
	}
	//returns true only if all playable pieces are filled
	else if (
		pieceVector[A1].display != " " && pieceVector[B1].display != " " && pieceVector[C1].display != " " &&
		pieceVector[A2].display != " " && pieceVector[B2].display != " " && pieceVector[C2].display != " " &&
		pieceVector[A3].display != " " && pieceVector[B3].display != " " && pieceVector[C3].display != " ") {
		cout << endl << "The game has ended in a draw. Run the program to play again!" << endl << "Turns in game: " << turns << endl;
		ofstream ofs("tictactoe.txt", ofstream::out);
		ofs << "NODATA";
		ofs.close();
		return true;
	}
	//returns false if at least one playable spot empty
	else {
		return false;
	}
}

//string
int TicTacToe::turn() {
	string currentP;
	//checks the current player
	if (playerX) {
		currentP = "Player X";
		currentDisp = "X";
	}
	else {
		currentP = "Player O";
		currentDisp = "O";
	}
	//print out current player
	cout << endl << currentP << ", ";
	playerX = !playerX;
	int hor;
	int vert;
	int promptInt = prompt(hor, vert);
	if (promptInt == QUIT_SAVE) {
		//save the game with ofstream 
		ofstream ofs ("tictactoe.txt", ofstream::out);
		ofs << "tictactoe" << endl
			<< currentDisp << " " <<  endl;
		for (int i = 0; i < turns; ++i) {
			for (int j = 0;j < 2;++j) {
				if (moveArray[i][j] > 0) {

					ofs << moveArray[i][j];
					if (j == 0) {
						ofs << " ";
					}
				}
			}
			ofs << endl;
		}
		ofs.close();		
		return QUIT_SAVE;
	}
	if (promptInt == QUIT_NO_SAVE) {
		//save the game with ofstream 
		ofstream ofs ("tictactoe.txt", ofstream::out);
		ofs << "NODATA";
		ofs.close();		
		return QUIT_NO_SAVE;
	}
	if (validPiece) {
		if (pieceVector[(vert + 1) * 5 - hor - 1].display == " ") {
			pieceVector[(vert + 1) * 5 - hor - 1].display = currentDisp;
			//moveArray[turns+1] = hor + "," + vert;
			moveArray[turns][0] = hor;
			moveArray[turns][1] = vert;
			turns++;
			cout << *this;
		}
		else {
			playerX = !playerX;
			return SPACE_OCCCUPIED;
		}
	}
	return promptInt;
}

//calls the extraction operator
void::TicTacToe::print() {
	cout << *this << endl;
}

//overloaded extraction operator for TicTacToe to print the board
ostream & operator << (ostream &out, const TicTacToe &game) {
	int line_counter = 4;
	for (int i = 25; i > 0; i--) {
		if ((i) % 5 == 0) {
			out << endl << line_counter;
			line_counter--;
		}
		out << game.pieceVector[i - 1].display << " ";
		//add in spaces for shorter than longest pieces
		if (game.longestDisp > game.pieceVector[i - 1].size) {
			int diff = game.longestDisp - game.pieceVector[i - 1].size;
			for (int i = 0;i < diff;i++) {
				out << " ";
			}
		}
	}
	out << endl << " ";
	int diff = game.longestDisp - 1;
	for (int i = 0;i < 5;i++) {
		out << i << " ";
		for (int i = 0;i < diff;i++) {
			out << " ";
		}
	}
	return out;
}