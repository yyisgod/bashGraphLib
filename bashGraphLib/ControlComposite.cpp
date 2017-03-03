/*************************************************************************
  File name:    ControlComposite.cpp
  Version:      1.0
  Description:  
  Author:       Yy <yyisgod@yeah.net>
  Create Date:  2017-02-21
 ************************************************************************/

#include "ControlComposite.h"

ControlComposite::ControlComposite(const char* name
	, uint height, uint width):Control(name) {
	try {
		_buf = new DisplayUnit(height, width);
	} catch (CreateError e) {
		e.baseClass = "ControlComposite";
		throw e;
	}
}

ControlComposite::~ControlComposite() {
	for(auto c = _controls.begin(); c != _controls.end(); c++) {
		if (*c != nullptr)
			delete *c;
	}
}

int ControlComposite::add(Control* ctl) {
	if (ctl == nullptr) {
		return -1;
	}

	_controls.push_back(ctl);

	return 0;
}

int ControlComposite::remove(Control* ctl) {
	if (ctl == nullptr) {
		return -1;
	}

	_controls.remove(ctl);

	return 0;
}

void ControlComposite::refresh() {
	_buf->clear();
	for(auto c = _controls.begin(); c != _controls.end(); c++) {
		if (*c != nullptr) {
			(*c)->copyTo(*this);
		}
	}
}
