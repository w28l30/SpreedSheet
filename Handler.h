#pragma once

#ifndef __HANDLER__H
#define __HANDLER__H

class Cell;
#include "list.h"
#include <vector>
#include <limits>
using namespace std;

class Handler
{
public:
	Handler(void);
	~Handler(void);

public:

	static int width;
	static int height;
	static const double NaN;

	static const string COMMAND_PRINT;
	static const string COMMAND_QUIT;
	static const string COMMAND_ADD_ROW;
	static const string COMMAND_REMOVE_ROW;
	static const string COMMAND_NUMBER;
	static const string COMMAND_STRING;
	static const string COMMAND_SET;
	static const string COMMAND_MEAN;
	static const string COMMAND_MIN;
	static const string COMMAND_MAX;

	static const string MSG_UNKNOW_COMMAND;
	static const string MSG_ROW_OUT_OF_RANGE;
	static const string MSG_CELL_OUT_OF_RANGE;
	static const string MSG_BAD_INPUT_FOR_SET_NUMBER;
	static const string MSG_FUNCTION_INCORRECT;

public:
	// check command validate
	static bool checkValidate(string& command,int row, int col, vector<string>& paraVec,LList<LList<Cell*>*>& ll);

	// process command
	static void processCommand(string& command,vector<string>& paraVec,LList<LList<Cell*>*>& ll);

	// print list
	static void print(LList<LList<Cell*>*>& ll); 
	static void print(LList<Cell*>* l);
private:
	// release memory of list
	static void quit(LList<LList<Cell*>*>& ll); 
	// add row
	static void addRow(int rowIndex, LList<LList<Cell*>*>& ll);
	// remove row
	static void removeRow(int rowIndex, LList<LList<Cell*>*>& ll);
	// set numeric cell value
	static void setNumericCellValue(int rowIndex,int colIndex,double data, LList<LList<Cell*>*>& ll);
	// set string cell value
	static void setStringCellValue(int rowIndex,int colIndex,string& str, LList<LList<Cell*>*>& ll);
	// set function cell value
	static void setFunctionCellValue(int rowIndex,int colIndex,int row, int begin,int end,int type, LList<LList<Cell*>*>& ll);
	// update cell data
	static void update(LList<LList<Cell*>*>& ll);

	static int checkChangeCount(LList<LList<Cell*>*>& ll,int count);
};


#endif