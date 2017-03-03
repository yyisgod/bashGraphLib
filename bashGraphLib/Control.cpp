/*************************************************************************
  File name:    Control.cpp
  Version:      1.0
  Description:  
  Author:       Yy <yyisgod@yeah.net>
  Create Date:  2017-02-20
 ************************************************************************/

#include "Control.h"
#include "Window.h"

const char* Control::name() {
	return _name;
}

Control::Control(const char* name) {
	if (name != nullptr)
		name = name;
	_top = 0;
	_left = 0;
	_buf = nullptr;
}

Control::~Control() {
	if (_buf != nullptr)
		delete _buf;
}

int Control::openColor() {
	return _buf->openColor();
}

int Control::draw(Window& win) {
	refresh();
	Rect rt(0, 0, _buf->getHeight(), _buf->getWidth());
	return win.insert(_top, _left, rt, *_buf);
}

int Control::getWidth() {
	return _buf->getWidth();
}
int Control::getHeight() {
	return _buf->getHeight();
}

int Control::setPosition(uint top, uint left) {
	_top = top;
	_left = left;
	return 0;
}

int Control::copyTo(Control& dst) {
	refresh();
	return dst.getFromBuf(_buf, _top, _left);
}

int Control::copyTo(Control& dst, uint top, uint left) {
	setPosition(top, left);
	return copyTo(dst);
}

int Control::getFromBuf(DisplayUnit* buf, uint top, uint left) {
	Rect rt(0, 0, buf->getHeight(), buf->getWidth());
	return _buf->insert(top, left, rt, *buf);
}

void Control::refresh() {}