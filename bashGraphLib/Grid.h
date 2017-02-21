/*************************************************************************
  File name:    Grid.h
  Version:      1.0
  Description:  Grid Control.
  				 Grid is like
  				 height = 4, width = 5
  				 gridgHeight = 1, gridWidth = 2, paddH = 1, paddW = 1
  				 ...........
  				 .*.*.*.*.*.
  				 .*.*.*.*.*.
  				 .*.*.*.*.*.
  				 .*.*.*.*.*.
  				 ...........
  Author:       Yy <yyisgod@yeah.net>
  Create Date:  2016-09-18
 ************************************************************************/

#ifndef _GRID_H
#define _GRID_H

#include "types.h"
#include "Control.h"

class Grid : public Control{
public:
	Grid(const char* name, uint height, uint width,
		uint gridHeight, uint gridWidth, uint paddH = 0, uint paddW = 0);
	virtual ~Grid();
	
	int set(uint x, uint y, char* str, int strLen = 1);
	int set(uint x, uint y, char* str, color c = none, int strLen = 1);
	void init(char ch = '.', color c = none);
	char getValue(uint x, uint y);

private:
	uint x2Top(uint x); //grid's bottom-right corner
	uint y2Left(uint y);

private:
	uint _gridHeight;
	uint _gridWidth;
	uint _paddH;
	uint _paddW;
};
#endif
