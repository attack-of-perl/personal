#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Lab4.h"
#include "gameBase.h"
using namespace std;

//--------------------------------------------------------------------

class Gomoku :public gameBase {
	friend ostream & operator << (ostream &out, const Gomoku &game);

public:
	Gomoku();
	virtual bool done();
	virtual bool draw();
	virtual int turn();
	virtual void print();
};

ostream & operator << (ostream &out, const Gomoku &game);
