/*************************************************************************
  File name:    Control.h
  Version:      1.0
  Description:  Base Class of Controls, Use Composite pattern
  Author:       Yy <yyisgod@yeah.net>
  Create Date:  2016-09-18
 ************************************************************************/

#ifndef _CONTROL_H
#define _CONTROL_H

#include "DisplayUnit.h"
#include "Window.h"
#include <list>

class Control{
public:
	virtual ~Control();

	const char* name();

	int openColor();
	virtual int draw(Window&);
	virtual int add(Control*){}; 
	virtual int remove(Control*){};
	virtual int resize(uint height, uint width){};
	int setPosition(uint top = 0, uint left = 0);
	virtual int copyTo(Control& dst);
	virtual int copyTo(Control& dst, uint top, uint left); 
	virtual int getFromBuf(DisplayUnit* buf, uint top = 0, uint left = 0);
	virtual std::list<Control*>::iterator createIterator(){};

protected:
	Control(const char* name);

protected:
	DisplayUnit* _buf;
	
	uint _top; // buf position
	uint _left;

private:
	const char* _name;

};
#endif
