/*************************************************************************
  File name:    graph.cpp
  Version:      1.0
  Description:  Definiation of class DisplayUnit
  Author:       Yy <yyisgod@yeah.net>
  Create Date:  2016-08-05
 ************************************************************************/

#include "DisplayUnit.h"
#include <iostream>
#include <cstring>

DisplayUnit::DisplayUnit(uint height, uint width){
	if ((_buf = new char*[height]) == NULL) {
		throw CreateError("DisplayUnit", "Malloc err");
		return;
	}

	for (int i = 0; i < height; i++) {
		if ((_buf[i] = new char[width]) == NULL) {
			throw CreateError("DisplayUnit", "Malloc err");
			return;
		}
		std::memset(_buf[i], ' ', width);
	}
	_height = height; _width = width;
	_colorBuf = NULL;
	_region = Rect(0, 0 ,height, width);
}

DisplayUnit::DisplayUnit(uint height, uint width, char** data):DisplayUnit(height, width){
	if (_buf != NULL && data != NULL){
		for (int i = 0; i < height; i++)
			std::memcpy((void*)_buf[i], (void*)data[i], width); 
	} else 
		throw Error("Input Error");
}

DisplayUnit::~DisplayUnit() { 
	deleteBuf();
}

int DisplayUnit::openColor() {
	if (_colorBuf != nullptr)
		return 0;

	if ((_colorBuf = new color*[_height]) == NULL) {
		return -1;
	}
	for (int i = 0; i < _height; i++) 
		if ((_colorBuf[i] = new color[_width]()) == NULL) {
			_colorBuf = NULL;
			return -1;
		}
	return 0;
}

int DisplayUnit::insert(int x, int y, Rect rtSrc, DisplayUnit& g) {
	if (adjust(x, y, rtSrc) == -1)
		return -1;
	
	for (int i = 0; i < rtSrc.height; i++) {
		if (std::memcpy(_buf[i + x] + y,
				g.getPointer(rtSrc.top + i, rtSrc.left), rtSrc.width) < 0)
			return -1;
	}

	if (_colorBuf && g.getColPointer(0, 0)) {
		for (int i = 0; i < rtSrc.height; i++) {
			if (std::memcpy(_colorBuf[i + x] + y,
					g.getColPointer(rtSrc.top + i, rtSrc.left), rtSrc.width) < 0)
				return -1;
		}
	}

	return 0;
}

int DisplayUnit::setRegion(int x, int y, Rect rtSrc, char** inData, color** c) { 
	if (inData == NULL && c == NULL)
		return -1;
	if (adjust(x, y, rtSrc) == -1)
		return -1;

	if (inData != NULL) {
		for (int i = 0; i < rtSrc.height; i++) {
			memcpy(_buf[x + i] + y
					, inData[rtSrc.top + i] + rtSrc.left, rtSrc.width);
		}
	}

	if (c != NULL && _colorBuf) {
		for (int i = 0; i < rtSrc.height; i++) {
			memcpy(_colorBuf[x + i] + y
					, c[rtSrc.top + i] + rtSrc.left, rtSrc.width);
		}
	}

	return 0;
}

int DisplayUnit::cpyRectTo(Rect rtSrc, uint x, uint y, char** outData, color** c) {
	if (outData == NULL)
		return -1;

	if (adjust(rtSrc) == -1)
		return -1;

	for (int i = 0; i < rtSrc.height; i++) {
		memcpy(outData[x + i] + y
				, _buf[rtSrc.top  + i] + rtSrc.left, rtSrc.width);
		outData++;
	}

	if (c != NULL && _colorBuf != NULL) {
		for (int i = 0; i < rtSrc.height; i++) {
			memcpy(c[x + i] + y
					, _colorBuf[rtSrc.top + i] + rtSrc.left, rtSrc.width);
			outData++;
		}
	}

	return 0;
}

char* const DisplayUnit::getPointer(uint top, uint left) {
	if (adjust((int&)top, (int&)left) == -1)
		return NULL;

	return (_buf[top] + left);
}

color* const DisplayUnit::getColPointer(uint top, uint left) {
	if (adjust((int&)top, (int&)left) == -1)
		return NULL;

	if (_colorBuf)
		return (_colorBuf[top] + left);
	else
		return NULL;
}

int DisplayUnit::setPoint(uint top, uint left, char ch, color c) {
	if (adjust((int&)top, (int&)left) == -1)
		return -1;

	if (ch != '\0')
		_buf[top][left] = ch;
	if (_colorBuf && c != none)
		_colorBuf[top][left] = c;
	return 0;
}

int DisplayUnit::setLine(uint top, uint left, uint len, const char* chs, color* c) {
	if (chs == NULL && c == NULL)
		return -1;
	Rect rt(0, 0, 1, len);
	if (adjust((int&)top, (int&)left, rt) == -1) 
		return -1;

	if (chs != NULL)
		memcpy(_buf[top] + left, chs, rt.width);
	if (_colorBuf && c)
		memcpy(_colorBuf[top] + left, c, rt.width);

	return 0;
}

void DisplayUnit::clear() {
	for (int i = _region.top; i < _region.height + _region.top; i++)
		memset(_buf[i] + _region.left, ' ', _region.width);
	if (_colorBuf)
		for (int i = _region.top; i < _region.height + _region.top; i++)
			memset(_colorBuf[i] + _region.left, none, _region.width);
}
void DisplayUnit::clear(char ch, color color) {
	for (int i = _region.top; i < _region.height + _region.top; i++)
			memset(_buf[i] + _region.left, ch, _region.width);

	if (_colorBuf == nullptr)
		openColor();

	for (int i = _region.top; i < _region.height + _region.top; i++)
			memset(_colorBuf[i] + _region.left, color, _region.width);
}

int DisplayUnit::clear(Rect rt) {
	if (adjust(rt) == -1)
		return -1;

	for (int i = rt.top; i < rt.height + rt.top; i++)
		std::memset(_buf[i] + rt.left, ' ', rt.width);

	if (_colorBuf)
		for (int i = rt.top; i < rt.height + rt.top; i++)
			std::memset(_colorBuf[i] + rt.left, none, rt.width);

	return 0;
}

// by rewrite _region, you just can get inner height and width
int DisplayUnit::getWidth() {
	return _region.width;
}

int DisplayUnit::getHeight() {
	return _region.height;
}

int DisplayUnit::refresh() {
	return 0;
}

int DisplayUnit::show() {
	if (_buf == NULL)
		return -1;
	
	refresh();

	if (!_colorBuf) // no color
		for (int i = 0; i < _height; i++) {
			for (int j = 0; j < _width; j++)
				std::cout << _buf[i][j];
			std::cout << std::endl;
		}
	else {
		for (int i = 0; i < _height; i++) {
			for (int j = 0; j < _width; j++)
				std::cout << colorsMap[_colorBuf[i][j]] << _buf[i][j];
			std::cout << std::endl;
		}
		std::cout << colorsMap[none];
	}

	return 0;
}

DisplayUnit::DisplayUnit() {}

void DisplayUnit::initDisplayUnit(int height, int width) {
	if ((_buf = new char*[height]) == NULL) {
		throw CreateError("DisplayUnit", "Malloc err");
		return;
	}

	for (int i = 0; i < height; i++) {
		if ((_buf[i] = new char[width]) == NULL) {
			throw CreateError("DisplayUnit", "Malloc err");
			return;
		}
		std::memset(_buf[i], ' ', width);
	}
	_height = height; _width = width;
	_colorBuf = NULL;
	_region = Rect(0, 0 ,height, width);
}

int DisplayUnit::adjust(int& x, int& y, Rect& dataRt) {
	int type = 0;
	if (x > _region.height + _region.top
		|| y > _region.width + _region.left)
		return -1;
	if (x < _region.top) { // top
		if (x + dataRt.height <= _region.top)
			return -1;
		type |= 1;
		dataRt.top += (_region.top - x);
		dataRt.height -= (_region.top - x);
		x = _region.top;
	}
	if (y < _region.left) { // left
		if (y + dataRt.width <= _region.left)
			return -1;
		type |= 2;
		dataRt.left += (_region.left - y);
		dataRt.width -= (_region.left - y);
		y = _region.left;
	}
	if (x + dataRt.height > _region.height + _region.top) { // bottom
		type |= 5;
		dataRt.height = _region.height - x;
	}
	if (y + dataRt.width > _region.width + _region.left) { // right
		type |= 6;
		dataRt.width = _region.width - y;
	}
	return type;
}

int DisplayUnit::adjust(Rect& rt) {
	int type = 0;
	if (rt.top > _region.height + _region.top
		|| rt.left > _region.width + _region.left)
		return -1;
	if (rt.top < _region.top) { // top
		if (rt.top + rt.height <= _region.top)
			return -1;
		type |= 1;
		rt.height -= (_region.top - rt.top);
		rt.top = _region.top;
	}
	if (rt.left < _region.left) { // left
		if (rt.left + rt.width <= _region.left)
			return -1;
		type |= 2;
		rt.width -= (_region.left - rt.left);
		rt.left = _region.left;
	}
	if (rt.top + rt.height > _region.top + _region.height) { // bottom
		type |= 5;
		rt.height = _region.height + _region.top - rt.top;
	}
	if (rt.left + rt.width > _region.width + _region.left) { // right
		type |= 6;
		rt.width = _region.width + _region.left - rt.left;
	}
	return type;
}

int DisplayUnit::adjust(int& x, int& y) {
	if (x < 0 || x >= _region.height + _region.top  
			|| y < 0 || y > _region.width + _region.left)
		return -1;
	return 0;
}

void DisplayUnit::deleteBuf() {
	if (_buf != nullptr) {
		delete []_buf;
	}
	if (_colorBuf != nullptr) {
		delete []_colorBuf;
	}
}