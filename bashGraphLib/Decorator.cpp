/*************************************************************************
  File name:    Decorator.cpp
  Version:      1.0
  Description:  
  Author:       Yy <yyisgod@yeah.net>
  Create Date:  2017-02-28
 ************************************************************************/

#include "Decorator.h"

Decorator::Decorator(const char* name, Control* ctl) : Control(name) {
	_ctl = ctl;
}

Decorator::~Decorator() {
	if (_ctl != nullptr)
		delete _ctl;
}

void Decorator::refresh() {
	_ctl->copyTo(*this); // refresh buf
}