/*************************************************************************
  File name:    win.cpp
  Version:      1.0
  Description:  
  Author:       Yy <yyisgod@yeah.net>
  Create Date:  2016-08-19
 ************************************************************************/

#include "Window.h"
#include <algorithm>
#include <cstring>

Margin Window::border(1, 1, 1, 1);

Window::~Window(){
}

Window::Window(uint height, uint width)
	:DisplayUnit(height + border.top + border.bottom
			, width + border.left + border.right) {
	_region = Rect(border.top, border.bottom
			, height
			, width);
	drawBorder();	
}

void Window::drawBorder() {
	for (int i = 1; i < _height - 1; i++)
		_buf[i][0] = _buf[i][_width - 1] = '|';

	std::memset(_buf[0]+1, '-', _width - 2);
	std::memset(_buf[_height-1]+1, '-', _width - 2);

	_buf[0][0] = _buf[0][_width-1] = '+';
	_buf[_height-1][0] = _buf[_height-1][_width-1] = '+';
}

int Window::adjust(int& x, int& y, Rect& dataRt) {
	x += border.top;
	y += border.left;
	return (DisplayUnit::adjust(x, y, dataRt));
}

int Window::adjust(Rect& rt) {
	rt.top += border.top;
	rt.left += border.left;
	return (DisplayUnit::adjust(rt));
}

int Window::adjust(int& x, int& y) {
	x += border.top;
	y += border.left;
	return (DisplayUnit::adjust(x, y));
}
