/*************************************************************************
  Copyright (C), 2016, TP-LINK TECHNOLOGIES CO., LTD.
  File name:    bombGame.h
  Version:      1.0
  Description:  game control
  Author:       Yan yu
  Create Date:  2016-08-19
 ************************************************************************/

#ifndef _BOMBGAME_H
#define _BOMBGAME_H

#include "bombBoard.h"

class BombGame {
public:
	BombGame(pKeyDealFunc keyDealFunc);
	~BombGame();
	void newGame(uint gameSize = 9, uint bombNum = 10);
	void refresh();
	int  dig(uint x, uint y);
	void setFlag(uint x, uint y);
	bool isWin();
	void wait();

private:
	void randSetBombs();
	bool isOver();
	void calNums();
	int calNumAround(uint x, uint y);
	void __dig(uint x, uint y);
	void displayBombs();

private:
	uint _gameSize;
	uint _bombNum;
	BombBoard *gameBoard;
	bool _gameOver;
	bool _isWin;
	bool* _mineGrid;
	char* _numGrid;
	pKeyDealFunc _keyDealFunc;
};

#endif
