#pragma once

#ifndef __STRING_CELL_H__
#define __STRING_CELL_H__

#include "Cell.h"

class StringCell : public Cell
{

private:
	string str;

public:
	StringCell(string& str);
	~StringCell(void);

public:
	void setData(string& s);
	string getData();
	string toString();
};

#endif