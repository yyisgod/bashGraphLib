/*************************************************************************
  Copyright (C), 2016, TP-LINK TECHNOLOGIES CO., LTD.
  File name:    bombBoard.h
  Version:      1.0
  Description:  view of bomb
  Author:       Yan yu
  Create Date:  2016-08-19
 ************************************************************************/

#ifndef _BOMBBOARD_H
#define _BOMBBOARD_H

#include "Window.h"
#include "Grid.h"
#include "ControlComposite.h"

class BombBoard {
public:
	const char FLAG = '^';
	const char BOMB = '@';
	const char BRICK = '#';
	const char BLANK = '.';

public:
	BombBoard(uint gameSize = 9);
	~BombBoard();

	void init();
	int setBrick(uint x, uint y);
	int setBomb(uint x, uint y);
	int setFlag(uint x, uint y);
	int setBlank(uint x, uint y);
	int setNum(uint x, uint y, uint num);
	char getGrid(uint x, uint y); //get grid status
	void print();

private:
	uint x2Top(uint x);
	uint y2Left(uint y);
	int setBLOCK(uint x, uint y, char ch, color c = none);

	void drawInnerRect();

private:
	Window *boardBg;
	ControlComposite *boardCC;
	Grid *boardGrid;
	uint left;
	uint top;
	uint _gameSize;

	static char markA[];
};

#endif
