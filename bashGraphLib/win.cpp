/*************************************************************************
  Copyright (C), 2016, TP-LINK TECHNOLOGIES CO., LTD.
  File name:    win.cpp
  Version:      1.0
  Description:  
  Author:       Yan yu
  Create Date:  2016-08-19
 ************************************************************************/

#include "win.h"
#include <algorithm>
#include <cstring>

Win::~Win(){
}

Win::Win(uint height, uint width):Graph(height, width) {
	drawBorder();	
}

void Win::clear() {
	for (int i = 1; i < _height - 1; i++)
		std::memset(_buf[i]+1, ' ', _width - 2);
}

void Win::clear(Rect rt) {
	if (rt.top >= _height - 1 || rt.left >= _width - 1)
		return;
	if (rt.top == 0)
		rt.top = 1;
	if (rt.left == 0)
		rt.left = 1;

	uint maxI = std::min(_height-1, rt.top + rt.height);
	uint maxJ = std::min(_width-1, rt.left + rt.width);

	for (int i = rt.top; i < maxI; i++)
		std::memset(_buf[i] + rt.left, ' ', maxJ - rt.left);

}

int Win::judge(Rect rt) {
	int errType = 0;
	if (rt.top == 0)
		errType |= (1 << 3);
	if (rt.left == 0)
		errType |= (1 << 2);
	if ((rt.top + rt.height) > _height - 1)
		errType |= (1 << 1);
	if ((rt.left + rt.width) > _width - 1)
		errType |= 1;

	return errType;
}

int Win::judge(Rect rt, Rect rtData) {
	int errType = 0;
	if (rt.top == 0)
		errType |= (1 << 3);
	if (rt.left == 0)
		errType |= (1 << 2);
	if (rt.height != rtData.height)
		errType |= 2;
	if (rt.width != rtData.width)
		errType |= 1;
	return (judge(rt) | errType);
}

int Win::judge(uint x, uint y) {
	int errType = 0;
	if (x == 0)
		errType |= 8;
	if (y == 0)
		errType |= 4;
	if (x >= _height - 1)
		errType |= 2;
	if (y >= _width - 1)
		errType |= 1;

	return errType;
}

void Win::drawBorder() {
	for (int i = 1; i < _height - 1; i++)
		_buf[i][0] = _buf[i][_width - 1] = '|';

	std::memset(_buf[0]+1, '-', _width - 2);
	std::memset(_buf[_height-1]+1, '-', _width - 2);

	_buf[0][0] = _buf[0][_width-1] = '+';
	_buf[_height-1][0] = _buf[_height-1][_width-1] = '+';
}
