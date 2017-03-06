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
#include "BorderDecorator.h"
#include <iostream>
#include <unistd.h>
using namespace std;

int deal(Window& win, string cmd, vector<string>& params);

int loop(Window& win);

int main() {
	Window win(50, 70, WindowStyle::Wide);
	win.openColor();

	ControlComposite *cc = new ControlComposite("cc1", 50, 60);
	cc->setPosition(0, 0);
	cc->openColor();

	Grid* g = new Grid("grid1", 4, 4, 2, 2, 1);
	BorderDecorator* bd = new BorderDecorator("borderDecorator", g, 2);
	bd->setBorder('/', '/', '/', '/', '/', '/', '/', '/');
	bd->openColor();
	bd->setColor(purple, yellow);
	g->init('.');
	g->set(0, 0, "abcd", 4);
	g->set(1, 0, "efgh", red, 4);
	g->set(2, 0, "****", blue, 4);
	g->set(3, 2, "[", cyan);
	bd->setPosition(1, 1);
	cc->add(bd);

	ControlComposite* cc2 = new ControlComposite("cc2", 20, 20);
	BorderDecorator* bd2 = new BorderDecorator("borderDecorator2", cc2, 4);
	bd2->setBorder('@', '@', '@', '@', '#', '#', '#', '#');
	bd2->openColor();
	bd2->setColor(brown, green);
	bd2->setPosition(20, 20);
	cc2->openColor();
	Grid* g2 = new Grid("grid2", 4, 4, 3, 3, 2);
	g2->setPosition(0, 0);
	g2->openColor();
	g2->init('*', blue);
	g2->set(0, 0, "yy", red, 2);
	g2->set(1, 1, "z", 1);
	cc2->add(g2);

	cc->add(bd2);

	win.add(cc);
	win.show();

	win.setKeyDealFunc(deal);

	win.start(loop);

	win.resize(10, 10, WindowStyle::Wide);
	win.show();

	return 0;
}

int deal(Window& win, string cmd, vector<string>& params) {
	cout << cmd;
	for(auto c = params.begin(); c != params.end(); c++) 
		cout << " " << *c;
	cout << endl;
	if (cmd == "q")
		return WindowMsgCode::EXIT_LOOP;
	win.show();

	return 0;
}

int loop(Window& win) {
	sleep(4);
	return WindowMsgCode::EXIT_LOOP;
}
