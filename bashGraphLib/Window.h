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
#include "ControlComposite.h"
#include "BorderDecorator.h"
#include <thread>
#include <vector>
#include <string>

namespace WindowStyle {
	enum WindowStyle {
		None,
		Thin, // + - |
		Wide // # @ @
	};
}

namespace WindowMsgCode {
	enum WindowMsgCode {
		EXIT_LOOP = -2	
	};
}

namespace WindowErrCode {
	enum WindowErrCode {
		NONE = 0,
		NULL_FUNC = -1,
	};
}

typedef int (*pKeyDealFunc)(Window& win, std::string cmd, std::vector<std::string>& params);
typedef int (*pLoopFunc)(Window& win);

class Window : public DisplayUnit {
public:
	Window(uint height, uint width, WindowStyle::WindowStyle style);
	//Window(uint height, uint width, char** data);
	virtual ~Window();
	int openColor();
	int add(Control* ctl);
	int remove(Control* ctl);
	virtual int resize(uint height, uint width, WindowStyle::WindowStyle style);

	int start(pLoopFunc loopFunc = nullptr); // start main loop
	void setKeyDealFunc(pKeyDealFunc keyDealFunc);

protected:
	virtual int refresh();
	/*
	virtual int adjust(int& x, int& y, Rect& dataRt);
	virtual int adjust(Rect& rt); // for output
	virtual int adjust(int& x, int& y);
	*/
private:
	static void inputFunc(Window& win, pKeyDealFunc func);
	int init(uint height, uint width, WindowStyle::WindowStyle style);

protected:
	Margin border;

private:
	BorderDecorator* _border;
	ControlComposite* _bufCtl;
	std::thread* _keyThread;
	pKeyDealFunc _keyDealFunc;
	bool _exitThread;	// exit loop
	bool _colorful;
};

#endif
