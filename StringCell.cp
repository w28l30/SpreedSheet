#include "StringCell.h"


StringCell::StringCell(string& str) : str(string(str.c_str()))
{
}


StringCell::~StringCell(void)
{
}


void StringCell::setData(string& s)
{
	str = string(s.c_str());
}

string StringCell::getData()
{
	return str;
}

string StringCell::toString()
{
	return str;
}

