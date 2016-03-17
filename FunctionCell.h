#pragma once

#ifndef __FUNCTION_CELL_H__
#define __FUNCTION_CELL_H__

#include "Cell.h"
#include "list.h"

class FunctionCell : public Cell
{

public:
	enum {MEAN, MIN, MAX};

private:
	int rowIndex;
	int beg;
	int end;
	double data;
	int type;
public:
	FunctionCell(int rowIndex,int beg,int end,int type);
	~FunctionCell(void);

public:
	void update(LList<Cell*>::iterator beg,LList<Cell*>::iterator end);
	string toString();
	void setData(double data);
	double getCellValue();
private:
	double mean(LList<Cell*>::iterator beg,LList<Cell*>::iterator end);
	double min(LList<Cell*>::iterator beg,LList<Cell*>::iterator end);
	double max(LList<Cell*>::iterator beg,LList<Cell*>::iterator end);

public:
	inline int getRowIndex() {return rowIndex;}
	inline int getBeg(){return beg;}
	inline int getEnd() {return end;}
	inline double getData() {return data;}
	inline int getType() {return type;}
};

#endif

