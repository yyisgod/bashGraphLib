/*************************************************************************
  File name:    BorderDecorator.cpp
  Version:      1.0
  Description:  
  Author:       Yy <yyisgod@yeah.net>
  Create Date:  2017-02-28
 ************************************************************************/

#include "BorderDecorator.h"

BorderDecorator::BorderDecorator(const char* name, Control* ctl, int width)
	: Decorator(name, ctl) {
	_borderWidth = width;	
	try {
		_buf = new	DisplayUnit(ctl->getHeight() + 2*width, ctl->getWidth() + 2*width); 
	} catch (CreateError e) {
		e.baseClass = "BorderDecorator";
		throw e;
	}
}

BorderDecorator::~BorderDecorator() {
}

void BorderDecorator::setBorder(char topChar, char botChar,  char leftChar, char rightChar,
					char leftTopChar, char rightTopChar,
					char leftBotChar, char rightBotChar) {
		_topChar = topChar;
		_botChar = botChar;
		_leftChar = leftChar;
		_rightChar = rightChar;
		_leftTopChar = leftTopChar;
		_rightTopChar = rightTopChar;
		_leftBotChar = leftBotChar;
		_rightBotChar = rightBotChar;
}

void BorderDecorator::setColor(color borderColor, color cornerColor) {
	_borderColor = borderColor;
	_cornerColor = cornerColor;
}

void BorderDecorator::refresh() {
	_ctl->copyTo(*this, _borderWidth, _borderWidth);
	// draw border
	for (int i = 0; i < _buf->getHeight(); i++)
		for (int j = 0; j < _buf->getWidth(); j++) {
			if (i < _borderWidth) {
				if (j < _borderWidth)
					_buf->setPoint(i, j, _leftTopChar, _cornerColor);
				else if (j >= _buf->getWidth() - _borderWidth)
					_buf->setPoint(i, j, _rightTopChar, _cornerColor);
				else
					_buf->setPoint(i, j, _topChar, _borderColor);
				continue;
			}
			if (i >= _buf->getHeight() - _borderWidth) {
				if (j < _borderWidth)
					_buf->setPoint(i, j, _leftBotChar, _cornerColor);
				else if (j >= _buf->getWidth() - _borderWidth)
					_buf->setPoint(i, j, _rightBotChar, _cornerColor);
				else
					_buf->setPoint(i, j, _botChar, _borderColor);
				continue;
			}
			if (j < _borderWidth)
				_buf->setPoint(i, j, _leftChar, _borderColor);
			else if (j >= _buf->getWidth() - _borderWidth)
				_buf->setPoint(i, j, _rightChar, _borderColor);
		}
}
