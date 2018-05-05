#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Lab4.h"
#include "gameBase.h"
using namespace std;

//--------------------------------------------------------------------

class TicTacToe :public gameBase {
	friend ostream & operator << (ostream &out, const TicTacToe &game);

public:
	TicTacToe();
	virtual bool done();
	virtual bool draw();
	virtual int turn();
	virtual void print();
};

ostream & operator << (ostream &out, const TicTacToe &game);

enum board_position {
	A3 = 18, B3 = 17, C3 = 16,
	A2 = 13, B2 = 12, C2 = 11,
	A1 = 8, B1 = 7, C1 = 6
};