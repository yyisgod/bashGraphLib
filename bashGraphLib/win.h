/*************************************************************************
  Copyright (C), 2016, TP-LINK TECHNOLOGIES CO., LTD.
  File name:    win.h
  Version:      1.0
  Description:  Win Class
  Author:       Yan yu
  Create Date:  2016-08-19
 ************************************************************************/

#ifndef _WIN_H
#define _WIN_H

#include "graph.h"

class Win : public Graph {
public:
	Win(uint height, uint width);
	Win(uint height, uint width, char** data);
	virtual ~Win();

	virtual void clear();
	virtual void clear(Rect rt);

protected:
	//Error type
	//0b		1		1		1		1
	//			top		left	bottom	right
	virtual int judge(Rect rt);
	virtual int judge(Rect rt, Rect rtData);
	virtual int judge(uint x, uint y);

protected:
	const int borderWidth = 1;

private:
	void drawBorder();

};
#endif
