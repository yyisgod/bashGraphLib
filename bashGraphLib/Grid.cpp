/*************************************************************************
  File name:    Grid.cpp
  Version:      1.0
  Description:  Grid Control
  Author:       Yy <yyisgod@yeah.net>
  Create Date:  2016-09-18
 ************************************************************************/

#include "Grid.h"
#include "Error.h"

Grid::Grid(const char* name, uint height, uint width,
		uint gridHeight, uint gridWidth, uint paddH, uint paddW):Control(name){
	try {
		_buf = new DisplayUnit((height-1)*gridHeight+1+paddH*2
						, (width-1)*gridWidth+1+paddW*2);
		
		_gridHeight = gridHeight;
		_gridWidth = gridWidth;
		_paddH = paddH;
		_paddW = paddW;

	} catch (CreateError e) {
		e.baseClass = "Grid";
		throw e;
	}
}

Grid::~Grid() {
}

void Grid::init(char ch, color c) {
	_buf->clear(ch ,c);
}

// 0 <= x < width
uint Grid::x2Top(uint x) {
	return (x * _gridHeight + _paddH);
}
uint Grid::y2Left(uint y) {
	return (y * _gridWidth + _paddW);	
}

int Grid::set(uint x, uint y, char* str, int strLen) {
	return set(x, y, str, none, strLen);
}

int Grid::set(uint x, uint y, char* str, color c, int strLen) {
	for (int i = y; i < y + strLen; i++) {
		_buf->setPoint(x2Top(x), y2Left(i), str[i - y], c);
	}

	return 0;
}

char Grid::getValue(uint x, uint y) {
	return *(_buf->getPointer(x2Top(x), y2Left(y)));
}