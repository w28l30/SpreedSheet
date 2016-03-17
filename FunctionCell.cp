#include "FunctionCell.h"
#include "Utils.h"
#include <iomanip>

FunctionCell::FunctionCell(int rowIndex,int beg,int end,int type)
	:rowIndex(rowIndex), beg(beg), end(end), type(type), data(numeric_limits<double>::quiet_NaN())
{
}


FunctionCell::~FunctionCell(void)
{
}

void FunctionCell::update(LList<Cell*>::iterator beg,LList<Cell*>::iterator end)
{
	switch(type)
	{
	case MEAN: data = mean(beg,end);break;
	case MIN:  data = min(beg,end);break;
	case MAX:  data = max(beg,end);break;
	default:;
	}
}

double FunctionCell::mean(LList<Cell*>::iterator beg,LList<Cell*>::iterator end)
{
	int count = 0;
	double NaN = numeric_limits<double>::quiet_NaN();
	double sum = NaN;
	double val;
	
	while(beg != end) 
	{
		if(*beg != nullptr)
		{
			val = (*beg)->getCellValue();
			if(!_isnan(val))
			{
				sum = _isnan(sum) ? val : sum + val;
				count++;
			}
		}
		beg++;
	} 

	return _isnan(sum) ? NaN : sum / count;
}

double FunctionCell::min(LList<Cell*>::iterator beg,LList<Cell*>::iterator end)
{
	double NaN = numeric_limits<double>::quiet_NaN();
	double minVal = NaN;
	double val;
	
	while(beg != end)
	{
		if(*beg != nullptr)
		{
			val = (*beg)->getCellValue();
			if(!_isnan(val))
			{
				minVal = _isnan(minVal) ? val : (val < minVal ? val : minVal);
			}
		}
		beg++;
	} 

	return minVal;
}

double FunctionCell::max(LList<Cell*>::iterator beg,LList<Cell*>::iterator end)
{
	double NaN = numeric_limits<double>::quiet_NaN();
	double maxVal = NaN;
	double val;
	
	while(beg != end) {
		if(*beg != nullptr)
		{
			val = (*beg)->getCellValue();
			if(!_isnan(val))
			{
				maxVal = _isnan(maxVal) ? val : (val > maxVal ? val : maxVal);
			}
		}
		beg++;
	}  

	return maxVal;
}


string FunctionCell::toString()
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

void FunctionCell::setData(double data)
{
	this->data = data;
}

double FunctionCell::getCellValue()
{
	return data;
}