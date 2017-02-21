/*************************************************************************
  File name:    test_Win.cpp
  Version:      1.0
  Description:  
  Author:       Yy <yyisgod@yeah.net>
  Create Date:  2016-08-19
 ************************************************************************/

#include "Window.h"
#include "Grid.h"
#include "ControlComposite.h"
#include <iostream>
using namespace std;

int main() {
	Window win(50, 70);
	win.show();
	win.openColor();

	ControlComposite cc("cc1", 50, 60);
	cc.setPosition(0, 0);
	cc.openColor();

	Grid* g = new Grid("grid1", 4, 4, 2, 2, 1);
	g->setPosition(1, 1);
	g->openColor();
	g->init('.');
	g->set(0, 0, "abcd", 4);
	g->set(1, 0, "efgh", red, 4);
	g->set(2, 0, "****", blue, 4);
	g->set(3, 2, "[", cyan);
	cc.add(g);
	cc.draw(win);

	win.show();

	ControlComposite* cc2 = new ControlComposite("cc2", 20, 20);
	cc2->setPosition(10, 10);
	cc2->openColor();
	Grid* g2 = new Grid("grid2", 4, 4, 3, 3, 2);
	g2->setPosition(0, 0);
	g2->openColor();
	g2->init('*', blue);
	g2->set(0, 0, "yy", red, 2);
	g2->set(1, 1, "z", 1);
	cc2->add(g2);

	cc.add(cc2);

	cc.draw(win);

	win.show();

	return 0;
}

