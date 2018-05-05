#include "stdafx.h"
#include "Lab4.h"
#include "gameBase.h"
#include "Sudoku.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <iomanip>
#include <set>
using namespace std;

Sudoku::Sudoku() {
	width = 24; height = 19; isSudoku = true;		//initializes
	gamePiece t("0");
	for (unsigned int i = 1; i < 82; ++i) {
		pieceVector.push_back(t);	//normal piecevector which updates throughout the game
		pVectINIT.push_back(t);		//second vector which only loads the sudoku0 initial game
	}
	ifstream ifs("sudoku.txt");
	if (ifs.is_open()) {
		string s;
		ifs >> s;
		if (s == "NODATA") {									//empty save file
			ifstream ifs("sudoku0");
			string temp;
			unsigned int i = 0;
			while (ifs >> temp) {
				pieceVector[i].display = temp;
				pVectINIT[i].display = temp;
				
				i++;
			}
			ifs.close();
			for (unsigned int i = 1; i < 82; ++i) {
				if (pieceVector[i - 1].display == "0") {		//change 0s to spaces
					pieceVector[i - 1].display = " ";
				}
			}
			for (unsigned int i = 1; i < 82; ++i) {
				if (pVectINIT[i - 1].display == "0") {			//change 0s to spaces
					pVectINIT[i - 1].display = " ";
				}
			}
		}
		else if (s == "sudoku") {							//using save file

			ifstream ifd("sudoku0");
			string temp2;
			unsigned int q = 0;
			while (ifd >> temp2) {
				pVectINIT[q].display = temp2;
				
				q++;
			}
			ifd.close();

			ifstream ifs("sudoku.txt");

			string temp;
			unsigned int i = 0;
			ifs >> temp;
			while (ifs >> temp) {
				pieceVector[i].display = temp;
				
				i++;
			}
			ifs.close();
			for (unsigned int i = 1; i < 82; ++i) {
				if (pieceVector[i - 1].display == "0") {			//change 0s to spaces
					pieceVector[i - 1].display = " ";
				}
			}
			for (unsigned int i = 1; i < 82; ++i) {
				if (pVectINIT[i - 1].display == "0") {				//change 0s to spaces
					pVectINIT[i - 1].display = " ";
				}
			}
		}
		else {
			cout << "Improperly formatted file (first_line)" << endl;
		}
	}
	else {
		ifstream if3("sudoku0");
		string temp3;
		unsigned int z = 0;
		while (if3 >> temp3) {
			pieceVector[z].display = temp3;
			pVectINIT[z].display = temp3;
			
			z++;
		}
		if3.close();
		for (unsigned int i = 1; i < 82; ++i) {
			if (pieceVector[i - 1].display == "0") {			//change 0s to spaces
				pieceVector[i - 1].display = " ";
			}
		}
		for (unsigned int i = 1; i < 82; ++i) {
			if (pVectINIT[i - 1].display == "0") {				//change 0s to spaces
				pVectINIT[i - 1].display = " ";
			}
		}
	}
}


bool Sudoku::draw() {
	//Always false; Sudoku is a single-player game
	return false;
}

bool Sudoku::done() {
	//return true;
	//checks straight across
	for (int i = 0;i <= 8;i++) {								//iterates through rows
		int counter = 0;										//counts number of distinct numbers
											
		for (int j = 0;j <= 8;j++) {							//iterates through individual line
			for (int check = 1;check <= 9;check++) {
				string checker = to_string(check);
				if (pieceVector[i * 9 + j].display == checker) {//checks if current piece is the same number as check
					counter++;
				}

			}

		}
			if (counter < 9) {
				return false;
			}
		
	}

	//checks straight down
	for (int i = 0;i <= 8;i++) {								//iterates through columns
		int counter = 1;										//counts number of distinct numbers

		for (int j = 0;j <= 8;j++) {							//iterates through individual column
			for (int check = 1;check <= 9;check++) {
				string checker = to_string(check);
				if (pieceVector[j * 9 + i].display == checker) {//checks if current piece is the same number as check
					counter++;
				}

			}	
		}
		if (counter < 9) {
			return false;
		}
	}

	//checks within each square
	//use sets for each box and iterate through the set
	for (auto g : BoxSet) {
		int counter = 0;
		for (auto f : g) {
			for (int check = 1;check <= 9;check++) {
				string checker = to_string(check);
				if (pieceVector[f].display == checker) {//checks if current piece is the same number as check
					counter++;
				}
			}	
		}
		if (counter < 9) {
			return false;
		}
	}
	return true;
}

int Sudoku::turn() {
	unsigned int horizontal;
	unsigned int vertical;
	unsigned int tile;
	prompt(horizontal, vertical, tile);
	if (!isFinished) {
		print();
	}
	return SUCCESS;
}

void Sudoku::prompt(unsigned int &horizontal, unsigned int &vertical, unsigned int &tile) {
	cout << "Please enter a coordinate pair followed by a value between 1 & 9 (e.g. '1,1,9'), or 'quit' to end the game." << endl;
	string input;
	getline(cin, input);
	lowerMaker(input);
	if (input == "quit") {
		isFinished = true; 
		//user chooses to quit and is prompted with the option to save their game state
		cout << "You have ended the game. " << "Would you like to save your current game?" << endl;
		string saveOrNot;
		while (saveOrNot != "yes" && saveOrNot != "no") {
			//keep pinging user for their answer
			cout << "Please type 'yes' to save or 'no' to not save your game." << endl;
			cin >> saveOrNot;
			lowerMaker(saveOrNot);
		}
		if (saveOrNot == "yes") {
			//reassign space tiles to a value of 0
			for (unsigned int i = 0; i < 81; ++i) {
				if (pieceVector[i].display == " ") {
					pieceVector[i].display = "0";
				}
			}
			//change sudoku.txt
			ofstream ofs("sudoku.txt", ofstream::out);
			ofs << "sudoku" << endl;
			for (int i = 0; i < 81; ++i) {
				if ((i + 1) % 9 == 0) {
					ofs << pieceVector[i].display << endl;
				}
				else {
					ofs << pieceVector[i].display << " ";
				}
			}
			ofs.close();
		}
		else if (saveOrNot == "no") {
			//overite game with ofstream 
			ofstream ofs("sudoku.txt", ofstream::out);
			ofs << "NODATA";
			ofs.close();
		}
	}
	else {
		//now change commas to spaces
		for (unsigned int i = 0;i < input.size();i++) {
			if (input[i] == ',') {
				input[i] = ' ';
			}
		}
		istringstream iss(input);
		
		if (iss >> horizontal >> vertical >> tile) {
			cout << tile << endl;
			if (horizontal < 0 || horizontal > 8 || vertical < 0 || vertical > 8 || tile < 1 || tile > 9) {
				cout << "Please enter coordinates with values from 0 to 8 followed by a number value from 1 to 9" << endl;
				validPiece = false;
			}
			else {
					
				if (pVectINIT[(horizontal)+(vertical * 9)].display != " ") {
					cout << "Space cannot be altered."<<endl;
				}
				else {
					gamePiece a = gamePiece(tile);
					pieceVector[(horizontal)+(vertical * 9)] = tile;
				}
			}
		}
		else {
			cout << "Make sure to use form 'x,y' for coordinates followed by a number 1-9" << endl;
			validPiece = false;
		}
		
	}
}


void Sudoku::print() {
	cout << *this << endl;
}


ostream & operator << (ostream &out, const Sudoku &game) {
	int line_counter = 8;
	for (int i = line_counter; i >= 0; --i) {
		if (line_counter % 3 != 0) {
			out << line_counter
				<< "||" << game.pieceVector[line_counter * 9].display
				<< "|" << game.pieceVector[line_counter * 9 + 1].display
				<< "|" << game.pieceVector[line_counter * 9 + 2].display
				<< "||" << game.pieceVector[line_counter * 9 + 3].display
				<< "|" << game.pieceVector[line_counter * 9 + 4].display
				<< "|" << game.pieceVector[line_counter * 9 + 5].display
				<< "||" << game.pieceVector[line_counter * 9 + 6].display
				<< "|" << game.pieceVector[line_counter * 9 + 7].display
				<< "|" << game.pieceVector[line_counter * 9 + 8].display
				<< "||" << endl;
			out << "-||-|-|-||-|-|-||-|-|-||" << endl;
		}
		else {
			out << line_counter
				<< "||" << game.pieceVector[line_counter * 9].display
				<< "|" << game.pieceVector[line_counter * 9 + 1].display
				<< "|" << game.pieceVector[line_counter * 9 + 2].display
				<< "||" << game.pieceVector[line_counter * 9 + 3].display
				<< "|" << game.pieceVector[line_counter * 9 + 4].display
				<< "|" << game.pieceVector[line_counter * 9 + 5].display
				<< "||" << game.pieceVector[line_counter * 9 + 6].display
				<< "|" << game.pieceVector[line_counter * 9 + 7].display
				<< "|" << game.pieceVector[line_counter * 9 + 8].display
				<< "||" << endl;
			out << "=||=|=|=||=|=|=||=|=|=||" << endl;
		}
		line_counter--;
	}
	out << "#||0|1|2||3|4|5||6|7|8||" << endl;
	return out;
}