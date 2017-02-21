/*************************************************************************
  File name:    Window.h
  Version:      1.0
  Description:  Window Class
  Author:       Yy <yyisgod@yeah.net>
  Create Date:  2016-08-19
 ************************************************************************/

#ifndef _WINDOW_H
#define _WINDOW_H

#include "DisplayUnit.h"

class Window : public DisplayUnit {
public:
	Window(uint height, uint width);
	Window(uint height, uint width, char** data);
	virtual ~Window();

protected:
	virtual int adjust(int& x, int& y, Rect& dataRt);
	virtual int adjust(Rect& rt); // for output
	virtual int adjust(int& x, int& y);

protected:
	static Margin border;

private:
	void drawBorder();
};

#endif
