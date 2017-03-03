/*************************************************************************
  File name:    types.h
  Version:      1.0
  Description:  types definition
  Author:       Yy <yyisgod@yeah.net>
  Create Date:  2016-08-05
 ************************************************************************/

#ifndef _TYPES_H
#define _TYPES_H

#define ERROR -1
#define RIGHT 1

#define C_NONE "\033[m"
#define C_RED "\033[0;32;31m"
#define C_LIGHT_RED "\033[1;31m"
#define C_GREEN "\033[0;32;32m"
#define C_LIGHT_GREEN "\033[1;32m"
#define C_BLUE "\033[0;32;34m"
#define C_LIGHT_BLUE "\033[1;34m"
#define C_DARK_GRAY "\033[1;30m"
#define C_CYAN "\033[0;36m"
#define C_LIGHT_CYAN "\033[1;36m"
#define C_PURPLE "\033[0;35m"
#define C_LIGHT_PURPLE "\033[1;35m"
#define C_BROWN "\033[0;33m"
#define C_YELLOW "\033[1;33m"
#define C_LIGHT_GRAY "\033[0;37m"
#define C_WHITE "\033[1;37m"

#include "Error.h"

enum color:char{
	none = 0,
	red,
	light_red,
	green,
	light_green,
	blue,
	light_blue,
	dark_gray,
	cyan,
	light_cyan,
	purple,
	light_purple,
	brown,
	yellow,
	light_gray,
	white
};

struct _colorMap {
	color c;
	string str;
};

const string colorsMap[16] = {
	C_NONE,
	C_RED,
	C_LIGHT_RED,
	C_GREEN,
	C_LIGHT_GREEN,
	C_BLUE,
	C_LIGHT_BLUE,
	C_DARK_GRAY,
	C_CYAN,
	C_LIGHT_CYAN,
	C_PURPLE,
	C_LIGHT_PURPLE,
	C_BROWN,
	C_YELLOW,
	C_LIGHT_GRAY,
	C_WHITE
};
typedef unsigned int uint;

struct Rect{
	int top;
	int left;
	int height;
	int width;

	Rect(int top, int left, int height, int width) {
		this->top = top;
		this->left = left;
		this->height = height;
		this->width = width;
	}

	Rect(){}
};

struct Margin {
	uint top;
	uint left;
	uint bottom;
	uint right;

	Margin(uint top, uint left, uint bottom, uint right) {
		this->top = top;
		this->left = left;
		this->bottom = bottom;
		this->right = right;
	}

	void set(uint top, uint left, uint bottom, uint right) {
		this->top = top;
		this->left = left;
		this->bottom = bottom;
		this->right = right;
	}
};

#endif
