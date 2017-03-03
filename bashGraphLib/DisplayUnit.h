/*************************************************************************
  File name:    DisplayUnit.h
  Version:      2.0
  Description:  ancestor of all class DisplayUnit
  Author:       Yy <yyisgod@yeah.net>
  Create Date:  2016-09-14
 ************************************************************************/

#ifndef _DISPLAYUNIT_H
#define _DISPLAYUNIT_H

#include "types.h"

class DisplayUnit{
public:
	DisplayUnit(uint height, uint width);
	DisplayUnit(uint height, uint width, char** data);
	virtual ~DisplayUnit();

	virtual int openColor();
	// return ERROR or RIGHT
	// insert a DisplayUint g into this at region(such as overlap)
	virtual int insert(int x, int y, Rect rtSrc, DisplayUnit& g);
	// insert data from inData
	virtual int setRegion(int x, int y, Rect rtSrc, char** inData, color** c = NULL);
	// copy region form _buf to outData 
	virtual int cpyRectTo(Rect rtSrc, uint x, uint y, char** outData, color** c = NULL);
	// return the pointer point to (left, top)
	virtual char* const getPointer(uint top, uint left);
	virtual color* const getColPointer(uint top, uint left);
	// set a char and color
	virtual int setPoint(uint top, uint left, char ch, color c = none);
	// set a line or color
	virtual int setLine(uint top, uint left, uint len, const char* chs, color* c = NULL);

	virtual void clear();
	virtual int clear(Rect rt);
	virtual void clear(char, color c = none);

	int getWidth();
	int getHeight();

	virtual int show();

protected:
	DisplayUnit();
	void initDisplayUnit(int height, int width); // used for later creater
	virtual int refresh();
	void deleteBuf();
	/************************************************************************
	 * descript the relative location of destination to this uint 
	 * and funciton will adjust the rt for part insert unless return types is -1.
	 *	return types:
	 *	-1 	: no overlap
	 * 	0 	: inner
	 *	1b 	: beyond the top border
	 *	10b : beyond the left border
	 * 	11b : cross the top-left corner
	 *	101b : beyond the bottom border
	 *	110b : right
	 *	111b : cross the right-bottom corner
	***************************************************************************/
	virtual int adjust(int& x, int& y, Rect& dataRt);
	virtual int adjust(Rect& rt); // for output
	virtual int adjust(int& x, int& y);

private:
	DisplayUnit(DisplayUnit&);
	DisplayUnit operator=(DisplayUnit&);
protected:
	char** _buf;
	color** _colorBuf;
	uint _height;
	uint _width;
	Rect _region;
};

#endif
