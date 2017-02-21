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

char BombBoard::markA[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

BombBoard::BombBoard(uint gameSize) {
	int height, width;
	
	if(gameSize < 27 && gameSize > 1) {
		_gameSize = gameSize;
		height = gameSize + 2 + 2;
		width = 2*gameSize + 1 + 2 + 2;
		left = 1;
		top = 1;
		if (gameSize > 9) 
			width += 2, left = 2;

		if((boardBg = new Window(height, width)) == NULL) {
			throw CreateError("BombBoard", "GameSize out");
		}
		if (boardBg->openColor() == -1)
			throw CreateError("BombBoard", "Colorize error");
		init();
	} else {
		throw CreateError("BombBoard", "GameSize out");
	}
}

BombBoard::~BombBoard() {
	delete boardBg;
	delete boardCC;
}

void BombBoard::init() {
	// composite, content all elements
	boardCC = new ControlComposite("boardCC", boardBg->getHeight()
				, boardBg->getWidth());
	boardCC->openColor();

	// makr: A B C D E ... 1 2 3 4 5...
	Grid *topMarkGrid = new Grid("topMarkGrid", 1, _gameSize, 1, 2, 0, 1);	
	topMarkGrid->openColor();
	topMarkGrid->setPosition(0, left + 1);
	topMarkGrid->set(0, 0, markA, blue, _gameSize);

	Grid *botMarkGrid = new Grid("botMarkGrid", 1, _gameSize, 1, 2, 0, 1);	
	botMarkGrid->openColor();
	botMarkGrid->setPosition(_gameSize + 3, left + 1);
	botMarkGrid->set(0, 0, markA, blue, _gameSize);

	Grid *leftMarkGrid = new Grid("leftMarkGrid", _gameSize, left, 1, 1, 1);
	leftMarkGrid->openColor();
	leftMarkGrid->setPosition(top, 0);

	Grid *rightMarkGrid = new Grid("rightMarkGrid", _gameSize, left, 1, 1, 1);
	rightMarkGrid->openColor();
	rightMarkGrid->setPosition(top, _gameSize*2 + 3 + left);
	for (int i = 0; i < _gameSize; i++) {
		char num[3] = { 0 };
		sprintf(num, "%d", i + 1);
		if (left == 2 && i < 10)
			leftMarkGrid->set(i, 1, num, blue, 1);
		else
			leftMarkGrid->set(i, 0, num, blue, 2);
		rightMarkGrid->set(i, 0, num, blue, strlen(num));
	}
	boardCC->add(topMarkGrid);
	boardCC->add(botMarkGrid);
	boardCC->add(leftMarkGrid);
	boardCC->add(rightMarkGrid);

	// core board
	boardGrid = new Grid("boardGrid", _gameSize, _gameSize, 1, 2, 0, 1);
	boardGrid->openColor();
	boardGrid->setPosition(top + 1, left + 1);

	for (int i = 0; i < _gameSize; i++)
		for ( int j = 0; j < _gameSize; j++) {
			setBrick(i, j);
		}

	boardCC->add(boardGrid);
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

char BombBoard::getGrid(uint x, uint y) {
	if ( x >= _gameSize || y >= _gameSize)
		return -1;
	return boardGrid->getValue(x, y);
}

void BombBoard::print() {
	boardCC->draw(*boardBg);
	drawInnerRect();
	boardBg->show();
}

int BombBoard::setBLOCK(uint x, uint y, char ch, color c) {
	if ( x >= _gameSize || y >= _gameSize)
		return -1;
	boardGrid->set(x, y, &ch, c);
	return 0;
}

void BombBoard::drawInnerRect() {
	for (int i = top + 1; i < top + _gameSize + 1; i++) {
		boardBg->setPoint(i, left+_gameSize*2+1+1, '|'); 
		boardBg->setPoint(i, left, '|');
	}

	std::memset(boardBg->getPointer(top, left + 1), '-', 2*_gameSize+1);
	std::memset(boardBg->getPointer(top+_gameSize+1, left + 1), '-', 2*_gameSize+1);

	boardBg->setPoint(top, left, '+');
	boardBg->setPoint(top, left+_gameSize*2+2, '+');
	boardBg->setPoint(top+_gameSize+1, left, '+');
	boardBg->setPoint(top+_gameSize+1, left+_gameSize*2+2, '+');
}
