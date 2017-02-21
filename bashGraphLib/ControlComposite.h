/*************************************************************************
  File name:    ControlComposite.h
  Version:      1.0
  Description:  controls composite base class
  Author:       Yy <yyisgod@yeah.net>
  Create Date:  2017-02-21
 ************************************************************************/

#ifndef _CONTROLCOMPOSITE_H
#define _CONTROLCOMPOSITE_H

#include <list>
#include "Control.h"
using std::list;

class ControlComposite : public Control {
public:
	virtual ~ControlComposite();
	ControlComposite(const char* name, uint height, uint width);

	virtual int draw(Window&);
	virtual int add(Control*); 
	virtual int remove(Control*);
	virtual int copyTo(Control& dst);
	
	virtual std::list<Control*>::iterator createIterator(){};

protected:
	// refresh buf data
	virtual int refresh();

private:
	list<Control*> _controls;
};
#endif