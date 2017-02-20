/*************************************************************************
  Copyright (C), 2016, TP-LINK TECHNOLOGIES CO., LTD.
  File name:    bombBoard.cpp
  Version:      1.0
  Description:  
  Author:       Yan yu
  Create Date:  2016-08-19
 ************************************************************************/

#include "bombBoard.h"
#include <cstring>

BombBoard::BombBoard(uint gameSize) {
	int height, width;
	
	if(gameSize < 27 && gameSize > 1) {
		_gameSize = gameSize;
		height = gameSize + 2 + 2 + 1 + 1;
		width = 2*gameSize + 1 + 2 + 2 + 2;
		left = 2;
		if (gameSize > 9) 
			width += 2, left = 3;
		if ((board = new Win(height, width)) == NULL) {
			throw CreateError("BombBoard", "GameSize out");
		}
		if (board->openColor() == -1)
			throw CreateError("BombBoard", "Colorize error");
		init();
	} else {
		throw CreateError("BombBoard", "GameSize out");
	}
}

BombBoard::~BombBoard() {
	delete board;
}

void BombBoard::init() {
	for (int i = top + 1; i < top + _gameSize + 1; i++) {
		board->setPoint(i, left+_gameSize*2+1+1, '|'); 
		board->setPoint(i, left, '|');
	}

	std::memset(board->getPointer(top, left + 1), '-', 2*_gameSize+1);
	std::memset(board->getPointer(top+_gameSize+1, left + 1), '-', 2*_gameSize+1);

	board->setPoint(top, left, '+');
	board->setPoint(top, left+_gameSize*2+2, '+');
	board->setPoint(top+_gameSize+1, left, '+');
	board->setPoint(top+_gameSize+1, left+_gameSize*2+2, '+');

	for (int i = 0; i < _gameSize; i++)
		for ( int j = 0; j < _gameSize; j++) {
			board->setPoint(x2Top(i), y2Left(j), BRICK, brown);
		}

	for (int j = 0; j < _gameSize; j++) {
		board->setPoint(1, y2Left(j), 'A' + j, blue);
		board->setPoint(1+_gameSize+2+1, y2Left(j), 'A'+j, blue);
	}

	for (int i = 1; i <= _gameSize; i++) {
		if (i < 10) {
			board->setPoint(2+i, left-1, '0' + i, blue);
			board->setPoint(2+i, left+_gameSize*2+1+2, '0' + i, blue);
		} else {
			board->setPoint(2+i, left-1, '0' + i % 10, blue);
			board->setPoint(2+i, left-2, '0' + i / 10, blue);
			board->setPoint(2+i, left+_gameSize*2+1+2, '0' + i / 10, blue);
			board->setPoint(2+i, left+_gameSize*2+1+2+1, '0' + i % 10, blue);
		}
	}
}

int BombBoard::setBrick(uint x, uint y) {
	return setBLOCK(x, y, BRICK, brown);
}

int BombBoard::setBomb(uint x, uint y) {
	return setBLOCK(x, y, BOMB, red);
}

int BombBoard::setFlag(uint x, uint y) {
	return setBLOCK(x, y, FLAG, light_red);
}

int BombBoard::setBlank(uint x, uint y) {
	return setBLOCK(x, y, BLANK, dark_gray);
}

int BombBoard::setNum(uint x, uint y, uint num) {
	if (num > 0 && num < 9) {
		color c;
		switch(num) {
		case 1:
			c = light_green;
			break;
		case 2:
			c = yellow;
			break;
		case 3:
			c = light_purple;
			break;
		case 4:
			c = purple;
			break;
		case 5:
			c = cyan;
			break;
		case 6:
			c = green;
			break;
		case 7:
			c = brown;
			break;
		case 8:
			c = white;
			break;
		}
		return setBLOCK(x, y, num+'0', c);
	} else
		return -1;
}

int BombBoard::getGrid(uint x, uint y) {
	if ( x >= _gameSize || y >= _gameSize)
		return -1;
	return *(board->getPointer(x2Top(x), y2Left(y)));
}

void BombBoard::print() {
	board->print();
}

uint BombBoard::x2Top(uint x) {
	return (top + 1 + x);
}

uint BombBoard::y2Left(uint y) {
	return (left + 2 + 2*y);
}

int BombBoard::setBLOCK(uint x, uint y, char ch, color c) {
	if ( x >= _gameSize || y >= _gameSize)
		return -1;
	board->setPoint(x2Top(x), y2Left(y), ch, c);
	return 0;
}

