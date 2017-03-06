/*************************************************************************
  Copyright (C), 2016, TP-LINK TECHNOLOGIES CO., LTD.
  File name:    main.cpp
  Version:      1.1
  Description:  mine Game
  Author:       Yan yu
  Create Date:  2016-09-06
 ************************************************************************/

#define C_NONE "\033[m"
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
int parse(Window& win, std::string cmd, std::vector<std::string>& params);
string sTolower(string& str);
void refresh();
BombGame game(parse);

bool isOver = false;

int main() { 
	string input;
	
	cout << "------------------------------\n";
	cout << RED << "Wellcome to mine game !\n" << C_NONE;
	cout << RED << "          author : yy\n" << C_NONE;
	cout << "------------------------------\n";

	cout << C_YELLOW << "Input gameSize[9] and mineNum[10]:" << C_NONE;
	uint gameSize, mineNum;
	getline(cin, input);
	if (input.empty()) {
		gameSize = 9, mineNum = 10;
	} else {
		if (sscanf(input.c_str(), "%u %u", &gameSize, &mineNum) < 2)
			gameSize = 9, mineNum = 10;
	}

	printf("Game set with gameSize = %u, mineNum = %u\n", gameSize, mineNum);

	newGame(game, gameSize, mineNum);

	refresh();
	game.wait();
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

int parse(Window& win, std::string cmd, std::vector<std::string>& params) {
	if (sTolower(cmd) == "n" || sTolower(cmd) == "new") {
		int x = 9, y = 10;
		if (params.size() == 2) {
			try {
				x = stoi(params[0]);
				y = stoi(params[1]);
			} catch (invalid_argument e) {
				goto help;
			}
		}

		if(newGame(game, x, y) != -1)
				game.refresh();

		return 0;
	}

	if (sTolower(cmd) == "q" || sTolower(cmd) == "quit") {
		cout << "Exiting game ...\n";
		cout << "Good bye!!!\n";

		return WindowMsgCode::EXIT_LOOP;
	}

	if (sTolower(cmd) == "f" || sTolower(cmd) == "flag") {
		if (params.size() == 2) {
			int x = 0, y = 0;
			try {
				x = stoi(params[0]) - 1;
				char ch = params[1][0];
				if (!isalpha(ch))
					goto help;	
				y = tolower(ch) - 'a'; 
			} catch (invalid_argument e) {
				goto help;
			}

			game.setFlag(x, y);
			game.refresh();
		} else
			goto help;
	}

	if (sTolower(cmd) == "d" || sTolower(cmd) == "dig") {
		if (params.size() == 2) {
			int x = 0, y = 0;
			try {
				x = stoi(params[0]) - 1;
				char ch = params[1][0];
				if (!isalpha(ch))
					goto help;	
				y = tolower(ch) - 'a'; 
			} catch (invalid_argument e) {
				goto help;
			}

			if (isOver) {
				cout << RED << "Game is over, please start a new game or quit\n" << C_NONE;
				goto next;
			}

			int status = game.dig(x, y);
			game.refresh();
			if (status == 1) {
				cout << RED << "You win!\n" << C_NONE;
				isOver = true;
				goto next;
			} else if (status == -1) {
				cout << RED <<"Victory and defeat are both common in battle\n"
					<< "Warrior please again.\n" << C_NONE;
				isOver = true;
				goto next;
			} else
				goto next;
		} else
			goto help;
	}

	if (sTolower(cmd) == "h" || sTolower(cmd) == "help") {
		goto help;
	}

help:
	printf(helpStr);
next:
	cout << C_YELLOW << "Input order: " << C_NONE;
	return 0;
}

string sTolower(string& str) {
	string r = str;
	for(int i = 0; i < r.length(); i++)
		r[i] = tolower(r[i]);

	return r;
}

void refresh() {
	game.refresh();
	cout << C_YELLOW << "Input order: " << C_NONE;
}