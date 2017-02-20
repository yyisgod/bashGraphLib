/*************************************************************************
  Copyright (C), 2016, TP-LINK TECHNOLOGIES CO., LTD.
  File name:    Error.h
  Version:      1.0
  Description:  Error类
  Author:       Yan yu
  Create Date:  2016-09-02
 ************************************************************************/

#ifndef _ERROR_H
#define _ERROR_H

#include <string>
using std::string;

class Error {
	Error();
public:
	Error(string msg_);
public:
	string msg;
};

class CreateError : public Error {
public:
	CreateError(string baseClass_, string msg_);
public:
	string baseClass;
};
#endif
