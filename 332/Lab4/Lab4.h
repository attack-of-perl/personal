#pragma once

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

#ifndef Lab4_h
#define Lab4_h

const int args = 2;			//expected number of arguments
const int filename = 0;		//for argv[0]
const int inputFile = 1;	//argv[1]

enum names {
	PROGRAM_NAME,
	FILE_NAME
};

enum failures {
	SUCCESS,
	DID_NOT_OPEN,
	TOO_MANY_ARGS,
	CANNOT_OPEN_FILE = 18,
	CANNOT_EXTRACT,
	CANNOT_GETLINE,
	COLOR_IS_INVALID,
	BAD_PIECE,
	GAME_QUIT_BY_USER,
	QUIT_SAVE,
	QUIT_NO_SAVE,
	SPACE_OCCCUPIED,
	DRAW,
	GOOD_PIECE,
	MEM_ERROR,
	NULL_PTR_EXCEPTION,
	NOT_NULL,
	BAD_GAME_NAME
};

void lowerMaker(string &input);

#endif // !Lab4_h
