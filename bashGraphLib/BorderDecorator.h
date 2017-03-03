/*************************************************************************
  File name:    BorderDecorator.h
  Version:      1.0
  Description:  
  Author:       Yy <yyisgod@yeah.net>
  Create Date:  2017-02-28
 ************************************************************************/

#ifndef _BORDERDECORATOR_H
#define _BORDERDECORATOR_H

#include "Decorator.h"

class BorderDecorator : public Decorator {
public:
	BorderDecorator(const char* name, Control* ctl, int width = 1);
	virtual ~BorderDecorator();

	void setBorder(char topChar, char botChar,  char leftChar, char rightChar,
					char leftTopChar, char rightTopChar,
					char leftBotChar, char rightBotChar);
	void setColor(color borderColor, color cornerColor);

protected:
	virtual void refresh();

private:
	int _borderWidth;
	char _topChar = '-';
	char _botChar = '-';
	char _leftChar = '|';
	char _rightChar = '|';
	char _leftTopChar = '+';
	char _rightTopChar = '+';
	char _leftBotChar = '+';
	char _rightBotChar = '+';
	color _borderColor = none;
	color _cornerColor = none;
};
#endif
