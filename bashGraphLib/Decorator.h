/*************************************************************************
  File name:    Decorator.h
  Version:      1.0
  Description:  
  Author:       Yy <yyisgod@yeah.net>
  Create Date:  2017-02-28
 ************************************************************************/

#ifndef _DECORATOR_H
#define _DECORATOR_H

#include "Control.h"

class Decorator : public Control {
public:
	virtual ~Decorator();

protected:
	Decorator(const char* name, Control* ctl);
	virtual void refresh();

protected:
	Control* _ctl;
};
#endif
