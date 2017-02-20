/*************************************************************************
  Copyright (C), 2016, TP-LINK TECHNOLOGIES CO., LTD.
  File name:    main.cpp
  Version:      1.1
  Description:  mine Game
  Author:       Yan yu
  Create Date:  2016-09-06
 ************************************************************************/

#define NONE "\033[m"
#define RED "\033[0;32;31m"
#include "bombGame.h"
#include <iostream>
#include <sstream>
using namespace std;

const char helpStr[] =
"GameOrder:\n"
" n [gameSize mineNum] - start a new game\n"
" d x y - dig the (x,y) block\n"
" f x y - flag the (x,y) block\n"
" q - quit\n"
" h - help\n"
"----------------\n"
"such as:\n"
" d 1 a\n"
" f 2 d\n";

int newGame(BombGame& game, uint gameSize, uint mineNum);
int parse(string order, uint& x, uint& y);

bool isOver = false;

int main() { 
	BombGame game;
	string input;
	
	cout << "------------------------------\n";
	cout << RED << "Wellcome to mine game !\n" << NONE;
	cout << RED << "          author : yy\n" << NONE;
	cout << "------------------------------\n";

	cout << YELLOW << "Input gameSize[9] and mineNum[10]:" << NONE;
	uint gameSize, mineNum;
	getline(cin, input);
	if (input.empty()) {
		gameSize = 9, mineNum = 10;
	} else {
		if (sscanf(input.c_str(), "%u %u", &gameSize, &mineNum) < 2)
			gameSize = 9, mineNum = 10;
	}

	printf("Game set with gameSize = %u, mineNum = %u\n", gameSize, mineNum);

	if (newGame(game, gameSize, mineNum) == -1)
		return -1;

	game.refresh();
	while(1) {
		string order;
		uint x, y;

		cout << YELLOW << "Input order: " << NONE;
		getline(cin, order);
		
		int rt;
		if ((rt = parse(order, x, y)) == -1) {
			cout << RED << "Input format error\n" << NONE;
			continue;
		}
		cout << LIGHT_CYAN << "-------------------------\n" << NONE;
		switch (rt) {
		case 0: {// dig
				if (isOver) {
					cout << RED << "Game is over, please start a new game or quit\n" << NONE;
					break;
				}
				int status = game.dig(x, y);
				game.refresh();
				if (status == 1) {
					cout << RED << "You win!\n" << NONE;
					isOver = true;
				} else if (status == -1) {
					cout << RED <<"Victory and defeat are both common in battle\n"
						<< "Warrior please again.\n" << NONE;
					isOver = true;
				}
			}
			break;
		case 1: // new game
			if(newGame(game, x, y) != -1)
				game.refresh();
			break;
		case 2: // quit
			goto out;
			break;
		case 3: // flag
			game.setFlag(x, y);
			game.refresh();
			break;

		case 4: // help
			printf(helpStr);
			break;
		}
		cout << LIGHT_CYAN << "-------------------------\n" << NONE;
	}

out:
		cout << "Exiting game ...\n";
		cout << "Good bye!!!\n";
		
		return 0;
}

int newGame(BombGame& game, uint gameSize, uint mineNum) {
	try {
		game.newGame(gameSize, mineNum);
		isOver = false;
	} catch (CreateError e) {
		cout << "XXXXXXXXXXXXXXXXXXXXXXXX\n";
		cout << e.baseClass << " create error!\n";
		return -1;
	} catch (Error e) {
		cout << e.msg << endl;
		return -1;
	}	

	return 0;
}

int parse(string order, uint& x, uint& y) {
	char c = '\0', a = '\0';
	istringstream o(order);
	o >> c;
	switch(c) {
	case 'n':
	case 'N':
		x = y = 0;
		o >> x >> y;
		if (x == 0 || y == 0) {
			x = 9;
			y = 10;
		}
		return 1;
		break;

	case 'q':
	case 'Q':
		return 2;
		break;

	case 'f':
	case 'F':
		x = y = 0;
		o >> x >> a;
		if ( x == 0 || a == '\0')
			return -1;
		else {
			x--;
			y = tolower(a) - 'a';
		}
		return 3;
		break;

	case 'h':
	case 'H':
		return 4;
		break;

	case 'd':
	case 'D':
		x = y = 0;
		o >> x >> a;
		if ( x == 0 || a == '\0' || !isalpha(a))
			return -1;
		else {
			x--;
			y = tolower(a) - 'a';
		}
		return 0;
		break;

	default:
		return 4;
	}
}

