/*************************************************************************
  Copyright (C), 2016, TP-LINK TECHNOLOGIES CO., LTD.
  File name:    Error.cpp
  Version:      1.0
  Description:  
  Author:       Yan yu
  Create Date:  2016-09-02
 ************************************************************************/

#include "Error.h"

Error::Error(string msg_) {
	msg = msg_;
}

CreateError::CreateError(string baseClass_, string msg_):Error(msg_) {
	baseClass = baseClass_;
}
