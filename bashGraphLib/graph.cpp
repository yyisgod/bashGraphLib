/*************************************************************************
  Copyright (C), 2016, TP-LINK TECHNOLOGIES CO., LTD.
  File name:    graph.cpp
  Version:      1.0
  Description:  Definiation of class Graph
  Author:       Yan yu
  Create Date:  2016-08-05
 ************************************************************************/

#include "graph.h"
#include <iostream>
#include <cstring>
string colorsMap[16] = {
	NONE,
	RED,
	LIGHT_RED,
	GREEN,
	LIGHT_GREEN,
	BLUE,
	LIGHT_BLUE,
	DARK_GRAY,
	CYAN,
	LIGHT_CYAN,
	PURPLE,
	LIGHT_PURPLE,
	BROWN,
	YELLOW,
	LIGHT_GRAY,
	WHITE
};

Graph::Graph(uint height, uint width){
	if ((_buf = new char*[height]) == NULL) {
		throw CreateError("Graph", "Malloc err");
		return;
	}

	for (int i = 0; i < height; i++) {
		if ((_buf[i] = new char[width]) == NULL) {
			throw CreateError("Graph", "Malloc err");
			return;
		}
		std::memset(_buf[i], ' ', width);
	}
	_height = height; _width = width;
	_colorBuf = NULL;
}

Graph::Graph(uint height, uint width, char** data):Graph(height, width){
	if (_buf != NULL && data != NULL){
		for (int i = 0; i < height; i++)
			std::memcpy((void*)_buf[i], (void*)data[i], width); 
	} else 
		throw Error("Input Error");
}

Graph::~Graph() {
	if (_buf) {
		for (int i = 0; i < _height; i++)
			delete []_buf[i];
		delete []_buf;
	}
	if (_colorBuf) {
		for (int i = 0; i < _height; i++)
			delete []_colorBuf[i];
		delete []_colorBuf;
	}
}

int Graph::openColor() {
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

int Graph::insert(Rect region, Graph& g, color c) { //color fake
	int errType = judge(region);
	if (errType != 0)
		return errType;
	
	for (int i = 0; i < region.height; i++) {
		std::memcpy(_buf[i + region.top] + region.left,
				g.getPointer(i, 0), region.width);
	}

	return 0;
}

int Graph::insert(Rect region_dst, Rect region_src, char** inData, color c) { //color fake
	if (inData == NULL)
		return -1;
	int errType = judge(region_dst, region_src);
	if (errType != 0)
		return errType;

	for (int i = 0; i < region_dst.height; i++) {
		memcpy(_buf[region_dst.top + i] + region_dst.left
				, inData[region_src.top] + region_src.left, region_dst.width);
		inData++;
	}
	return 0;
}

int Graph::cpyRectTo(Rect region_src, Rect region_dst, char** outData) {
	if (outData == NULL)
		return -1;

	int errType = judge(region_src, region_dst);
	if (errType != 0)
		return errType;

	for (int i = 0; i < region_src.height; i++) {
		memcpy(outData[region_src.top + i] + region_src.left
				, _buf[region_dst.top + i] + region_dst.left, region_src.width);
		outData++;
	}
	return 0;
}

char* Graph::getPointer(uint top, uint left) {
	if (top >= _height || left >= _width)
		return NULL;

	return (_buf[top] + left);
}


int Graph::setPoint(uint top, uint left, char ch, color c) {
	int errType = judge(top, left);
	if (errType)
		return errType;

	_buf[top][left] = ch;
	if (_colorBuf)
		_colorBuf[top][left] = c;
	return 0;
}

int Graph::setLine(uint top, uint left, uint len, const char* chs, color c) {
	if (chs == NULL)
		return -1;
	int errType = judge(Rect(top, left, 1, len));
	if (errType)
		return errType;

	std::memcpy(_buf[top] + left, chs, len);
	if (_colorBuf)
		std::memset(_colorBuf[top] + left, c, len);
	return 0;
}

void Graph::clear() {
	for (int i = 0; i < _width; i++)
		memset(_buf[i], ' ', _width );
	if (_colorBuf)
		for (int i = 0; i < _width; i++)
			memset(_colorBuf[i], none, _width);
}

int Graph::getWidth() {
	return _width;
}

int Graph::getHeight() {
	return _height;
}

int Graph::print() {
	if (_buf == NULL)
		return -1;
	
	if (!_colorBuf)
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

int Graph::judge(Rect rt) {
	int errType = 0;
	if ((rt.top + rt.height) > _height)
		errType |= (1 << 1);
	if ((rt.left + rt.width) > _width)
		errType |= 1;

	return errType;
}

int Graph::judge(Rect rt, Rect rtData) {
	int errType = 0;
	if (rt.height != rtData.height)
		errType |= 2;
	if (rt.width != rtData.width)
		errType |= 1;
	return (judge(rt) | errType);
}

int Graph::judge(uint x, uint y) {
	int errType = 0;
	if (x >= _height)
		errType |= 2;
	if (y >= _width)
		errType |= 1;

	return errType;
}
