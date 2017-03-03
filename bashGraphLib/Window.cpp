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
#include <thread>
#include <sstream>
#include <iostream>
#include <chrono>
#include <system_error>
using namespace std;

Window::~Window(){
	if (_border != nullptr)
		delete _border;
	if (_keyThread != nullptr)
		delete _keyThread;
}

Window::Window(uint height, uint width, WindowStyle::WindowStyle style) 
	:border(1, 1, 1, 1) {
	init(height, width, style);
}

int Window::openColor() {
	_colorful = true;
	_bufCtl->openColor();
	_border->openColor();
	return DisplayUnit::openColor();
}

int Window::add(Control* ctl) {
	return _bufCtl->add(ctl);
}

int Window::remove(Control* ctl) {
	return _bufCtl->remove(ctl);
}

int Window::refresh() {
	return _border->draw(*this);
}

int Window::start(pLoopFunc loopFunc) {
	if (_keyDealFunc == nullptr) {
		return WindowErrCode::NULL_FUNC;
	}

	try {
		_keyThread = new thread(inputFunc, std::ref(*this), _keyDealFunc);
	} catch (system_error e) {
		cout << "KeyThead create failed " << endl << e.what() << endl;
	}

	if (loopFunc != nullptr)
		if (loopFunc(*this) == WindowMsgCode::EXIT_LOOP) {
			// force exit keyThread if loopFunc is not a while(1)
			_exitThread = true;
			cout << "Press Enter to exit...\n";
		}

	_keyThread->join();	// wait 

	return WindowErrCode::NONE;
}

void Window::setKeyDealFunc(pKeyDealFunc keyDealFunc) {
	_keyDealFunc = keyDealFunc;
}

void Window::inputFunc(Window& win, pKeyDealFunc func) {
	while (!win._exitThread) {
		string cmdLine;

		getline(cin, cmdLine);	
		if (cmdLine.length() == 0) {
			continue;
		}

		istringstream cmdS(cmdLine);

		string cmd;
		cmdS >> cmd;
		if (cmd.length() == 0)
			continue;

		string param;
		vector<string> params;

		while (!cmdS.eof()) {
			cmdS >> param;
			params.push_back(param);
		}

		if (func(win, cmd, params) == WindowMsgCode::EXIT_LOOP)
			break;
	}
}

int Window::resize(uint height, uint width, WindowStyle::WindowStyle style) {
	if (_border != nullptr)
		delete _border;
	deleteBuf();

	bool colorful = _colorful;

	init(height, width, style);

	if (colorful)
		openColor();
}

int Window::init (uint height, uint width, WindowStyle::WindowStyle style) {
	switch (style) {
	case WindowStyle::None:
		border.set(0, 0, 0, 0);
		break;
	case WindowStyle::Thin:
		border.set(1, 1, 1, 1);
		break;
	case WindowStyle::Wide:
		border.set(2, 2, 2, 2);
		break;
	default:
		border.set(1, 1, 1, 1);
	}

	try {
		initDisplayUnit(height + border.top + border.bottom,
							width + border.left + border.right);

		_bufCtl = new ControlComposite("winBufComposite", height, width);
		_border = new BorderDecorator("winBorder", _bufCtl, border.top);
	} catch (CreateError e) {
		e.baseClass = "Window";
		throw e;
	}

	switch (style) {
	case WindowStyle::None:
		break;
	case WindowStyle::Thin:
		_border->setBorder('-', '-', '|', '|', '+', '+', '+', '+');
		break;
	case WindowStyle::Wide:
		_border->setBorder('#', '#', '#', '#', '@', '@', '@', '@');
		break;
	default:
		break;
	}	

	_region = Rect(0, 0
			, height + border.top + border.bottom
			, width + border.left + border.right);

	_exitThread = false;
	_colorful = false;

	return WindowErrCode::NONE;
}

/*
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
*/