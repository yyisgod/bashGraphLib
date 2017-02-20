/*************************************************************************
  Copyright (C), 2016, TP-LINK TECHNOLOGIES CO., LTD.
  File name:    graph.h
  Version:      1.0
  Description:  ancestor of all class Graph
  Author:       Yan yu
  Create Date:  2016-08-05
 ************************************************************************/

#ifndef _GRAPH_H
#define _GRAPH_H

#include "types.h"

class Graph{
public:
	Graph(uint height, uint width);
	Graph(uint height, uint width, char** data);
	virtual ~Graph();

	virtual int openColor();
	// return ERROR or RIGHT
	// insert a Garph g into this at region
	virtual int insert(Rect region, Graph& g, color c = none);
	// insert data from inData, use stride insert in _buf region
	virtual int insert(Rect region_dst, Rect region_src, char** inData, color c = none);
	// copy region for _buf to outData by the stride
	virtual int cpyRectTo(Rect region_src, Rect region_dst, char** outData);
	// return the pointer point to (left, top)
	virtual char* getPointer(uint top, uint left);
	// set a char
	virtual int setPoint(uint top, uint left, char ch, color c = none);
	// set a line
	virtual int setLine(uint top, uint left, uint len, const char* chs, color c = none);

	virtual void clear();

	int getWidth();
	int getHeight();
	int print();

protected:
	virtual int judge(Rect rt);
	virtual int judge(Rect rt, Rect rtData);
	// return 2 for x error, 1 for y error
	virtual int judge(uint x, uint y);

private:
	Graph();
	Graph(Graph&);
	Graph operator=(Graph&);
protected:
	char** _buf;
	color** _colorBuf;
	uint _height;
	uint _width;
};

#endif
