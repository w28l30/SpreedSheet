#pragma once

#ifndef __CELL_H__
#define __CELL_H__

#include <string>
using namespace std;

class Cell
{
public:
	Cell(void);
	virtual ~Cell(void);

public:
	virtual string toString();
	virtual double getCellValue();
};

#endif