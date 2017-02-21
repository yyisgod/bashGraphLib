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

#define NONE "\033[m"
#define RED "\033[0;32;31m"
#define LIGHT_RED "\033[1;31m"
#define GREEN "\033[0;32;32m"
#define LIGHT_GREEN "\033[1;32m"
#define BLUE "\033[0;32;34m"
#define LIGHT_BLUE "\033[1;34m"
#define DARK_GRAY "\033[1;30m"
#define CYAN "\033[0;36m"
#define LIGHT_CYAN "\033[1;36m"
#define PURPLE "\033[0;35m"
#define LIGHT_PURPLE "\033[1;35m"
#define BROWN "\033[0;33m"
#define YELLOW "\033[1;33m"
#define LIGHT_GRAY "\033[0;37m"
#define WHITE "\033[1;37m"

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
};

#endif
