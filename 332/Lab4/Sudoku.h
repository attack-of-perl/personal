#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Lab4.h"
#include "gameBase.h"
#include <set>

using namespace std;

class Sudoku :public gameBase {
	friend ostream & operator << (ostream &out, const Sudoku &game);

public:
	Sudoku();
	virtual bool done();
	virtual void prompt(unsigned int &horizontal, unsigned int &vertical, unsigned int &tile);
	virtual int turn();
	virtual void print();
	virtual bool draw();
};

ostream & operator << (ostream &out, const Sudoku &game);

enum sudoku_position {
	AA1,AA2,AA3,A4,A5,A6,A7,A8,A9,
	BB1,BB2,BB3,B4,B5,B6,B7,B8,B9,
	CC1,CC2,CC3,C4,C5,C6,C7,C8,C9,
	D1,D2,D3,D4,D5,D6,D7,D8,D9,
	E1,E2,E3,E4,E5,E6,E7,E8,E9,
	F1,F2,F3,F4,F5,F6,F7,F8,F9,
	G1,G2,G3,G4,G5,G6,G7,G8,G9,
	H1,H2,H3,H4,H5,H6,H7,H8,H9,
	I1,I2,I3,I4,I5,I6,I7,I8,I9

};

//each "box" is a 3x3 within the sudoku board that must
//contain every number 1-9 to win the game
static set<int> aBox1 = {
	AA1, AA2, AA3,BB1,BB2,BB3,CC1,CC2,CC3
};

static set<int> aBox2 = {
	A4,A5,A6,B4,B5,B6,C4,C5,C6
};

static set<int> aBox3 = {
	A7,A8,A9,B7,B8,B9,C7,C8,C9
};

static set<int> aBox4 = {
	D1,D2,D3,E1,E2,E3,F1,F2,F3
};

static set<int> aBox5 = {
	D4,D5,D6,E4,E5,E6,F4,F5,F6
};

static set<int> aBox6 = {
	D7,D8,D9,E7,E8,E9,F7,F8,F9
};

static set<int> aBox7 = {
	G1,G2,G3,H1,H2,H3,I1,I2,I3
};

static set<int> aBox8 = {
	G4,G5,G6,H4,H5,H6,I4,I5,I6
};

static set<int> aBox9 = {
	G7,G8,G9,H7,H8,H9,I7,I8,I9
};

static set<set<int>> BoxSet = {
	aBox1, aBox2, aBox4, aBox5, aBox6, aBox7, aBox8, aBox9
};