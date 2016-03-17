#pragma once

#ifndef __NUMERIC_CELL_H__
#define __NUMERIC_CELL_H__

#include "Cell.h"
 
class NumericCell : public Cell
{

private:
	double data;
public:
	NumericCell(double data);
	~NumericCell(void);
public:
	void setData(double data);
	double getData();
	double getCellValue();
	virtual string toString();
};

#endif
