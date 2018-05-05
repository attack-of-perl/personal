#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include "Lab4.h"
using namespace std;

//--------------------------------------------------------------------

struct gamePiece {
	string display;
	int size;
	gamePiece(string a);
	gamePiece(unsigned int anInt);
};

//--------------------------------------------------------------------

class gameBase {

protected:
	int logestSize;
	int player;
	int height;
	int width;
	int turns;
	int longestDisp;
	bool playerX = true;
	bool validPiece;
	int realHeight;
	int realWidth;
	string currentDisp;
	string inputDisp;
	vector<gamePiece> pieceVector;
	vector<gamePiece> pVectINIT;
	static shared_ptr<gameBase> ptr;

public:
	gameBase();
	virtual bool done() = 0;
	virtual bool draw() = 0;
	virtual int prompt(int &a, int &b);
	virtual int turn() = 0;
	int play();
	virtual void print() = 0;
	void updateLongest(int a);
	static void baseArgs(int argc, char* argv[]);
	static shared_ptr<gameBase> instance();
	int moveArray[600][3]; //arbitrarily large
	bool isSudoku=false;
	bool isFinished=false;
};
