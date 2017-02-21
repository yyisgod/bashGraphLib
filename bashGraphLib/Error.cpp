/*************************************************************************
  File name:    Error.cpp
  Version:      1.0
  Description:  
  Author:       Yy <yyisgod@yeah.net>
  Create Date:  2016-09-02
 ************************************************************************/

#include "Error.h"

Error::Error(string msg_) {
	msg = msg_;
}

CreateError::CreateError(string baseClass_, string msg_):Error(msg_) {
	baseClass = baseClass_;
}

BorderCrossError::BorderCrossError(string className, string msg):Error(msg) {
	this->className = className;
}
