#include "stdafx.h"
#include "Lab4.h"
#include "gameBase.h"
#include "Gomoku.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <iomanip>

//-----------------------------------------------------------------------
//Gomoku

Gomoku::Gomoku() {
	width = 19; height = 19; longestDisp = 0; realHeight = 19; realWidth = 19; turns = 0;
	ifstream ifs("gomoku.txt");
	gamePiece t(" ");
	for (int i = 1; i <= width*height;++i) {
		pieceVector.push_back(t);
	}
	if (ifs.is_open()) {
		string s;
		ifs >> s;
		
		if (s == "NODATA") {
			//nothing to read
		}
		else if (s == "gomoku") {
			//loads previously saved game
			ifstream ifs;
			ifs.open("gomoku.txt");
			string aString;
			string string2;
			if (ifs.is_open()) {
				getline(ifs, string2);
				getline(ifs, string2);
				istringstream is1(string2);
				is1 >> currentDisp;
				inputDisp = "B";
				turns = 0;
				while (getline(ifs, aString)) {
					if (aString[0] == ' ') {
						cout << "BREAKBREAK" << endl;
						break;
					}
					istringstream iss(aString);
					int vert; int hor;
					iss >> hor >> vert;
					if (hor > 0 && pieceVector[(vert - 1) * width + hor - 1].display == " ") {

						pieceVector[(vert - 1) * width + hor - 1].display = inputDisp;
						moveArray[turns][0] = hor;
						moveArray[turns][1] = vert;
						turns++;
						if (inputDisp == "B") {
							inputDisp = "W";
							playerX = !playerX;
						}
						else if (inputDisp == "W") {
							inputDisp = "B";
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

//overloaded print method
void Gomoku::print() {
	cout << *this << endl;
}

bool Gomoku::done() {
	//check horizontally and vertically for 5 in a row
	for (int i = 0; i < 18; ++i) {
		int whiteV = 0;
		int blackV = 0;
		int blackH = 0;
		int whiteH = 0;
		for (int j = 0; j < 18; ++j) {
			if (pieceVector[width * i + j].display == " ") {
				blackH = 0; whiteH = 0;
			}
			if (pieceVector[width * j + i].display == " ") {
				blackV = 0; whiteV = 0;
			}
			if (pieceVector[width * i + j].display == "W") {
				blackH = 0; ++whiteH;
				if (whiteH == 5) {
					//winning condition, rewrite file to NODATA
					ofstream ofs("gomoku.txt", ofstream::out);
					ofs << "NODATA";
					ofs.close();
					return true;
				}
			}
			if (pieceVector[width * i + j].display == "B") {
				whiteH = 0; ++blackH;
				if (blackH == 5) {
					//winning condition, rewrite file to NODATA
					ofstream ofs("gomoku.txt", ofstream::out);
					ofs << "NODATA";
					ofs.close();
					return true;
				}
			}
			if (pieceVector[width * j + i].display == "W") {
				blackV = 0; ++whiteV;
				if (whiteV == 5) {
					//winning condition, rewrite file to NODATA
					ofstream ofs("gomoku.txt", ofstream::out);
					ofs << "NODATA";
					ofs.close();
					return true;
				}
			}
			if (pieceVector[width * j + i].display == "B") {
				whiteV = 0; ++blackV;
				if (blackV == 5) {
					//winning condition, rewrite file to NODATA
					ofstream ofs("gomoku.txt", ofstream::out);
					ofs << "NODATA";
					ofs.close();
					return true;
				}
			}
		}
	}
	//check diagonally for 5 in a row
	for (int i = 0; i < 18; ++i) {
		int counter = i * 19;
		int bDiagNegative = 0;
		int bDiagPositive = 0;
		int wDiagNegative = 0;
		int wDiagPositive = 0;
		//check positive slope diagonals for 5 in a row
		while (counter < 19 * 19) {
			if (pieceVector[counter].display == "W") {
				++wDiagPositive; bDiagPositive = 0;
				if (wDiagPositive == 5) {
					//winning condition, rewrite file to NODATA
					ofstream ofs("gomoku.txt", ofstream::out);
					ofs << "NODATA";
					ofs.close();
					return true;
				}
			}
			if (pieceVector[counter].display == "B") {
				++bDiagPositive; wDiagPositive = 0;
				if (bDiagPositive == 5) {
					//winning condition, rewrite file to NODATA
					ofstream ofs("gomoku.txt", ofstream::out);
					ofs << "NODATA";
					ofs.close();
					return true;
				}
			}
			if (pieceVector[counter].display == " ") {
				wDiagPositive = 0; bDiagPositive = 0;
			}
			counter += 19 + 1;
		}
		counter = i;
		//check negative slope diagonals for 5 in a row
		while (counter < 19 * 19) {
			if (pieceVector[counter].display == "W") {
				++wDiagNegative; bDiagNegative = 0;
				if (wDiagNegative == 5) {
					//winning condition, rewrite file to NODATA
					ofstream ofs("gomoku.txt", ofstream::out);
					ofs << "NODATA";
					ofs.close();
					return true;
				}
			}
			if (pieceVector[counter].display == "B") {
				++bDiagNegative; wDiagNegative = 0;
				if (bDiagNegative == 5) {
					//winning condition, rewrite file to NODATA
					ofstream ofs("gomoku.txt", ofstream::out);
					ofs << "NODATA";
					ofs.close();
					return true;
				}
			}
			if (pieceVector[counter].display == " ") {
				wDiagNegative = 0; bDiagNegative = 0;
			}
			counter += 19 + 1;
		}
	}
	return false;
}

bool Gomoku::draw() {
	bool someEmpty = false;
	for (int i = 1;i < 19;i++) {
		for (int j = 1;j < 19;j++) {
			if (pieceVector[width*i + j].display == " ") {
				someEmpty = true;
			}
		}
	}
	if (done()) {
		return false;
	}

	//returns true only if all playable pieces are filled
	else if (!someEmpty) {
		cout << endl << "The game has ended in a draw. Run the program to play again!" << endl << "Turns in game: " << turns << endl;
		return true;
	}
	//returns false if at least one playable spot empty
	else {
		return false;
	}
}

int Gomoku::turn() {
	string currentP;
	//checks the current player
	if (playerX) {
		currentP = "Player B";
		currentDisp = "B";
	}
	else {
		currentP = "Player W";
		currentDisp = "W";
	}
	//print out current player
	cout << endl << currentP << ", ";
	playerX = !playerX;
	int hor;
	int vert;
	int promptInt = prompt(hor, vert);
	if (promptInt == QUIT_SAVE) {
		//save the game with ofstream 
		ofstream ofs("gomoku.txt", ofstream::out);
		ofs << "gomoku" << endl
			//<< *this << endl
			<< currentDisp << " " << endl;
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
		ofstream ofs("gomoku.txt", ofstream::out);
		ofs << "NODATA";
		ofs.close();
		return QUIT_NO_SAVE;
	}
	if (validPiece) {
		if (pieceVector[(vert - 1) * width + hor - 1].display == " ") {
			pieceVector[(vert - 1) * width + hor - 1].display = currentDisp;
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

//overloaded extraction operator for Gomoku to print the board
ostream & operator << (ostream &out, const Gomoku &game) {
	out << endl;
	int row = game.width;
	for (int i = 0; i < game.width; i++) {
		out << setw(2);
		out << row << " ";
		for (int j = 0; j < game.height; j++) {
			out << game.pieceVector[(game.height*game.width - 1 - (game.height - j - 1) - (game.width * i))].display << "  ";
		}
		out << endl;
		row--;
	}
	out << "X  ";
	for (int i = 1;i < 10;i++) {
		out << i << "  ";
	}
	for (int i = 10;i < game.height + 1;i++) {
		out << i << " ";
	}
	out << endl;
	return out;
}