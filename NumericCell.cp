#include "NumericCell.h"
#include "Utils.h"

NumericCell::NumericCell(double data) : data(data)
{
}


NumericCell::~NumericCell(void)
{
}


void NumericCell::setData(double data)
{
	this->data = data;
}

double NumericCell::getData()
{
	return data;
}

string NumericCell::toString()
{
	string str = Utils::toString<double>(data);
	int index = str.find(".");
	if(index == -1)
	{
		str += ".000000";
	}
	else
	{
		int len = str.length() - 1 - index;
		if(len > 0 && len < 6)
		{
			for(int i=0;i<6 - len;i++)
				str +="0";
		}
	}
	return str;
}

double NumericCell::getCellValue()
{
	return data;
}