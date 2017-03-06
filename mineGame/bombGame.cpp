/*************************************************************************
  Copyright (C), 2016, TP-LINK TECHNOLOGIES CO., LTD.
  File name:    bombGame.cpp
  Version:      1.0
  Description:  
  Author:       Yan yu
  Create Date:  2016-08-20
 ************************************************************************/

#include "bombGame.h"
#include <ctime>
#include <cstdlib>

BombGame::BombGame(pKeyDealFunc keyDealFunc) {
	gameBoard = NULL;
	_keyDealFunc = keyDealFunc;
}

void BombGame::newGame(uint gameSize, uint bombNum) { 
	if (bombNum >= gameSize * gameSize || bombNum < 1){
		throw CreateError("BombGame", "bombNum err");
	} else {
		_bombNum = bombNum;
		_gameOver = false; // no over
		_gameSize = gameSize;
		_isWin = false;
		if (_mineGrid != nullptr)
			delete _mineGrid;
		if (_numGrid != nullptr)
			delete _numGrid;
		_mineGrid = new bool[_gameSize * _gameSize]();
		_numGrid = new char[_gameSize * _gameSize]();
		randSetBombs();
		calNums();

		if (gameBoard == nullptr) {
			try {
				gameBoard = new BombBoard(gameSize);
				gameBoard->start(_keyDealFunc);
			} catch (Error e) {
				gameBoard = NULL;
				throw e;
			}
		} else {
			gameBoard->newBoard(gameSize);
		}
	}
}

BombGame::~BombGame() {
	if (gameBoard)
		delete gameBoard;
}

void BombGame::refresh() {
	gameBoard->print();
}

int BombGame::dig(uint x ,uint y) {
	if (x >= _gameSize || y >= _gameSize)
		return -2; // input error

	__dig(x, y);
	bool over = isOver();
	if (over) {
		if (_isWin)
			return 1;
		else {
			displayBombs();
			return -1;
		}
	} else
		return 0;
}

void BombGame::setFlag(uint x, uint y) {
	if (gameBoard->getGrid(x, y) == gameBoard->FLAG) {
		gameBoard->setBrick(x, y);
		return;
	}
	if (gameBoard->getGrid(x, y) == gameBoard->BRICK) {
		gameBoard->setFlag(x, y);	
		return;
	}
}

bool BombGame::isWin() {
	return _isWin;
}

void BombGame::randSetBombs() {
	std::srand(unsigned(time(0)));
	int up = _gameSize * _gameSize;
	for (int i = 0; i < _bombNum; i++) {
		int index = ((double)std::rand() / (RAND_MAX)) * up;
		if (_mineGrid[index])
			i--;
		else
			_mineGrid[index] = true;
	}
}

bool BombGame::isOver() {
	if (_gameOver)
		return true;
	int count = 0;
	for (int x = 0; x < _gameSize; x++)
		for (int y = 0; y < _gameSize; y++) {
			char ch = gameBoard->getGrid(x, y);
			if (ch == gameBoard->FLAG && !_mineGrid[x*_gameSize+y])
				return false;
			if (ch == gameBoard->BRICK) {
				if (!_mineGrid[x*_gameSize+y])
					return false;
				count++;
			}
		}

	if (count > _bombNum)
		return false;
	else {
		_isWin = true;
		_gameOver = true;
		return true;
	}
}

void BombGame::calNums() {
	int up = _gameSize * _gameSize;
	for (int i = 0 ; i < up; i++) {
		if (!_mineGrid[i])
			_numGrid[i] = calNumAround(i / _gameSize, i % _gameSize);
	}
}

int BombGame::calNumAround(uint x, uint y) {
	int xMin = x > 0 ? x-1 : x;
	int xMax = x < _gameSize-1 ? x+1 : x;
	int yMin = y > 0 ? y-1 : y;
	int yMax = y < _gameSize-1 ? y+1 : y;

	int bombCount = 0;
	for (int i = xMin; i <= xMax; i++)
		for (int j = yMin; j <= yMax; j++) {
			int index = i*_gameSize + j;
			if (_mineGrid[index])
				bombCount++;
		}

	return bombCount;
}

void BombGame::__dig(uint x, uint y) {
	char ch = gameBoard->getGrid(x ,y);
	if (_gameOver) // game was over
		return;
	if (ch == gameBoard->FLAG)
		return;
	if (ch == gameBoard->BLANK)
		return;
	if (_mineGrid[x*_gameSize+y]) {
		_gameOver = true;
		_isWin = false;
		gameBoard->setBomb(x, y);
		return;
	}
	
	if (_numGrid[x*_gameSize+y] != 0) {
		gameBoard->setNum(x, y, _numGrid[x*_gameSize+y]);
		return;
	}

	gameBoard->setBlank(x, y);
	int xMin = x > 0 ? x-1 : x;
	int xMax = x < _gameSize-1 ? x+1 : x;
	int yMin = y > 0 ? y-1 : y;
	int yMax = y < _gameSize-1 ? y+1 : y;

	for (int i = xMin; i <= xMax; i++)
		for (int j = yMin; j <= yMax; j++) {
			ch = gameBoard->getGrid(i, j);
			if (ch == gameBoard->BRICK && !_mineGrid[i*_gameSize+j])
				dig(i, j);
		}
}

void BombGame::displayBombs() {
	for (int i = 0; i < _gameSize*_gameSize; i++) {
		if (_mineGrid[i])
			gameBoard->setBomb(i/_gameSize, i%_gameSize);
	}
}

void BombGame::wait() {
	gameBoard->wait();
}
