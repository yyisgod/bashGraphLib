/*************************************************************************
  File name:    Error.h
  Version:      1.0
  Description:  Error类
  Author:       Yy <yyisgod@yeah.net>
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

class BorderCrossError : public Error {
public:
	BorderCrossError(string className, string msg);
public:
	string className;
};

#endif
