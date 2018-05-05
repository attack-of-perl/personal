// Lab4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Lab4.h"
#include "gameBase.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <memory>

using namespace std;


int usageMessage(char*arg) {
	cout << "usage: " << arg << " TicTacToe/Gomoku/Sudoku" << endl;
	return TOO_MANY_ARGS;
}

void lowerMaker(string &input) {
	string aString;

	for (unsigned int i = 0;i < input.length();++i) {	//iterates through string 
		if (input[i] >= 65 && input[i] <= 91) {			//checks if char is uppercase
			input[i] = input[i] + 32;					//changes to lowercase if above condition is met
		}
	}
}


int main(int argc, char * argv[])
{
	try {
		gameBase::baseArgs(argc,argv);
		//game = shared_ptr<gameBase>(gameBase::baseArgs(argc, argv));
	}
	catch (bad_alloc b) {
		return MEM_ERROR;
	}
	catch (failures e) {
		cout << "Pointer not null. Exception:" << e << endl;
		return e;
	}
	shared_ptr<gameBase> game = gameBase::instance();
	if (game != nullptr) {
		return game->play();
	}
	else {
		return usageMessage(argv[filename]);
	}
}

