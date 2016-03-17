#include "Cell.h"
#include <limits>
using namespace std;

Cell::Cell(void)
{
}


Cell::~Cell(void)
{
}

string Cell::toString()
{
	return "";
}

double Cell::getCellValue()
{
	return numeric_limits<double>::quiet_NaN();
}