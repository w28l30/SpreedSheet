#include "Handler.h"
#include <iostream>
#include <iomanip>
#include <sstream>

#include "NumericCell.h"
#include "StringCell.h"
#include "FunctionCell.h"
#include "Utils.h"

const double Handler::NaN = numeric_limits<double>::quiet_NaN();
const string Handler::COMMAND_PRINT = "print";
const string Handler::COMMAND_QUIT = "quit";
const string Handler::COMMAND_ADD_ROW = "addrow";
const string Handler::COMMAND_REMOVE_ROW = "removerow";
const string Handler::COMMAND_SET = "set";
const string Handler::COMMAND_NUMBER = "number";
const string Handler::COMMAND_STRING = "string";
const string Handler::COMMAND_MEAN = "mean";
const string Handler::COMMAND_MIN = "min";
const string Handler::COMMAND_MAX = "max";
const string Handler::MSG_UNKNOW_COMMAND = "Error: unknown command";
const string Handler::MSG_ROW_OUT_OF_RANGE = "Error: row out of range";
const string Handler::MSG_CELL_OUT_OF_RANGE = "Error: cell out of range";
const string Handler::MSG_BAD_INPUT_FOR_SET_NUMBER = "Error: Bad input for set number";
const string Handler::MSG_FUNCTION_INCORRECT = "Error: function incorrect";

Handler::Handler(void)
{
}


Handler::~Handler(void)
{
}

int Handler::width;
int Handler::height;

/*
	check whether the input command is valid
	if command is valid, return true
	else print error msg and return false
*/
bool Handler::checkValidate(string& command,int row, int col, vector<string>& paraVec,LList<LList<Cell*>*>& ll)
{
	row = ll.getSize();
	istringstream iss(command);
	string para;
	while(iss >> para)
	{
		paraVec.push_back(para);
	}

	//1. check print or quit
	if(paraVec.size() == 1 && (paraVec[0] == COMMAND_PRINT || paraVec[0] == COMMAND_QUIT))
	{
		return true;
	}
	
	//2. check addRow x , removeRow x
	if(paraVec.size() > 1  && (paraVec[0] == COMMAND_ADD_ROW || paraVec[0] == COMMAND_REMOVE_ROW))
	{
		// x is not integer or x is out of range
		if(!Utils::isAbleToType<int>(paraVec[1]))
		{
			cout << MSG_ROW_OUT_OF_RANGE << endl;
			return false;
		}
		int index = Utils::toType<int>(paraVec[1]);
		if(index < 0 || index >= row)
		{
			cout << MSG_ROW_OUT_OF_RANGE << endl;
			return false;
		}
		return true;
	}

	//3. check set x y type value, there are 3 cases;
	   //1. if type == number ,  paraVec.size() == 5 , [set x y number z]
				//x,y must be integer, z can be convert to double
	   //2. if type == string ,  paraVec.size() >= 5 , [set x y string z]
				// x,y must be integer
	   //3. if type == mean,min,max paraVec.size() == 7 , [set x y mean/min/max p q r] 
				// x,y,p,q,r must be integer
	/*bool ret1 = paraVec.size() == 5 && paraVec[3] == COMMAND_NUMBER && Utils::isAbleToType<int>(paraVec[1])
		&& Utils::isAbleToType<int>(paraVec[2]);   
	bool ret2 = paraVec.size() >= 5 && paraVec[3] == COMMAND_STRING && Utils::isAbleToType<int>(paraVec[1])
		&& Utils::isAbleToType<int>(paraVec[2]);
	bool ret3 = paraVec.size() == 7 && (paraVec[3] == COMMAND_MEAN || paraVec[3] == COMMAND_MIN || paraVec[3] == COMMAND_MAX)
		&& Utils::isAbleToType<int>(paraVec[1]) && Utils::isAbleToType<int>(paraVec[2]) && Utils::isAbleToType<int>(paraVec[4])
		&& Utils::isAbleToType<int>(paraVec[5]) && Utils::isAbleToType<int>(paraVec[6]);*/
	
	bool ret1 = paraVec.size() > 4 && paraVec[3] == COMMAND_NUMBER && Utils::isAbleToType<int>(paraVec[1])
		&& Utils::isAbleToType<int>(paraVec[2]);   
	bool ret2 = paraVec.size() > 4 && paraVec[3] == COMMAND_STRING && Utils::isAbleToType<int>(paraVec[1])
		&& Utils::isAbleToType<int>(paraVec[2]);
	bool ret3 = paraVec.size() == 7 && (paraVec[3] == COMMAND_MEAN || paraVec[3] == COMMAND_MIN || paraVec[3] == COMMAND_MAX)
		&& Utils::isAbleToType<int>(paraVec[1]) && Utils::isAbleToType<int>(paraVec[2]) && Utils::isAbleToType<int>(paraVec[4])
		&& Utils::isAbleToType<int>(paraVec[5]) && Utils::isAbleToType<int>(paraVec[6]);

	if(ret1 || ret2 || ret3)
	{
		// check whether x,y is out of range
		int x = Utils::toType<int>(paraVec[1]);  //col
		int y = Utils::toType<int>(paraVec[2]);  //row
		if(x < 0 || y < 0 || x > col-1 || y > row-1)
		{
			cout << MSG_CELL_OUT_OF_RANGE << endl;
			return false;
		}

		// bad input for set number
		if(ret1 && !Utils::isAbleToType<double>(paraVec[4]))
		{
			cout << MSG_BAD_INPUT_FOR_SET_NUMBER << endl;
			return false;
		}

		// function incorrect
		if(ret3)
		{
			int p = Utils::toType<int>(paraVec[4]);
			int q = Utils::toType<int>(paraVec[5]);
			int r = Utils::toType<int>(paraVec[6]);
			if(p < 0 || p > row || q < 0 || q > col || r < 0 || r > col) {
				cout << MSG_FUNCTION_INCORRECT << endl;
				return false;
			}
		}

		return true;
	}

	
	//4. otherwise, the input command is invalid
	cout << MSG_UNKNOW_COMMAND << endl;
	return false;
}


void Handler::processCommand(string& command, vector<string>& paraVec,LList<LList<Cell*>*>& ll)
{
	if(paraVec[0] == COMMAND_PRINT)
	{
		print(ll);
	}
	else if(paraVec[0] == COMMAND_QUIT)
	{
		quit(ll);
	}
	else 
	{
		if(paraVec[0] == COMMAND_ADD_ROW)
		{
			addRow(Utils::toType<int>(paraVec[1]),ll);
		}
		else if(paraVec[0] == COMMAND_REMOVE_ROW)
		{
			removeRow(Utils::toType<int>(paraVec[1]),ll);
		}
		else if(paraVec[0] == COMMAND_SET)
		{
			int colIndex = Utils::toType<int>(paraVec[1]);
			int rowIndex = Utils::toType<int>(paraVec[2]);
			if(paraVec[3] == COMMAND_NUMBER)
			{
				double data = Utils::toType<double>(paraVec[4]);
				setNumericCellValue(rowIndex,colIndex,data,ll);
			}
			else if(paraVec[3] == COMMAND_STRING)
			{
				string str = command.substr(command.find(paraVec[4]));
				setStringCellValue(rowIndex,colIndex,str,ll);
			}
			else  // function cell
			{
				int row = Utils::toType<int>(paraVec[4]);
				int begin = Utils::toType<int>(paraVec[5]);
				int end = Utils::toType<int>(paraVec[6]);
				int type = -1;
				if(paraVec[3] == COMMAND_MEAN)
				{
					type = FunctionCell::MEAN;
				}
				if(paraVec[3] == COMMAND_MIN)
				{
					type = FunctionCell::MIN;
				}
				else if(paraVec[3] == COMMAND_MAX)
				{
					type = FunctionCell::MAX;
				}
				
				setFunctionCellValue(rowIndex,colIndex,row,begin,end,type,ll);
			}
		}

		// update cell data
		update(ll);
	}
}


void Handler::print(LList<LList<Cell*>*>& ll)
{
	for(LList<Cell*>* l : ll) 
	{
		print(l);
	}
	// cout a blank line
	//cout << endl;
}

void Handler::print(LList<Cell*>* l)
{
	if(l != nullptr)
	{
		LList<Cell*>::iterator ita = l->begin();
		int n = l->getSize() - 1;
		while(ita != l->end())
		{
			Cell* c = *ita++;
			if(c != nullptr) 
			{
				cout << c->toString();
			}

			if(n--)
			{
				cout << ",";
			}
		}
		cout << endl;
	}
}

/*
	release memory of every element of ll
*/
void Handler::quit(LList<LList<Cell*>*>& ll)
{
	for(LList<Cell*>* l : ll) 
	{
		delete l;
	}
}


void Handler::addRow(int rowIndex, LList<LList<Cell*>*>& ll)
{
	//cout << endl << "addRow, rowIndex=" << rowIndex << endl;
	LList<Cell*>* l = new LList<Cell*>;
	Cell* ptr = nullptr;
	for(int j=0;j<width;j++)
	{
		l->push_back(ptr);
	}
	ll.insert(l,rowIndex);
}


void Handler::removeRow(int rowIndex, LList<LList<Cell*>*>& ll)
{
	//cout << endl << "removeRow, rowIndex=" << rowIndex << endl;
	delete *(ll.get(rowIndex)); // release memory
	ll.remove(rowIndex);
}

void Handler::setNumericCellValue(int rowIndex,int colIndex,double data, LList<LList<Cell*>*>& ll)
{
	//cout << endl << "set numeric cell value, rowIndex=" << rowIndex << " colIndex=" << colIndex << " data=" << data << endl;
	Cell* c = new NumericCell(data);
	LList<Cell*>* l = (*ll.get(rowIndex));
	delete *(l->get(colIndex)); // release memory
	l->set(c,colIndex);
}

void Handler::setStringCellValue(int rowIndex,int colIndex,string& str, LList<LList<Cell*>*>& ll)
{
	//cout << endl << "set string cell value, rowIndex=" << rowIndex << " colIndex=" << colIndex << " str=" << str << endl;
	Cell* c = new StringCell(str);
	LList<Cell*>* l = (*ll.get(rowIndex));
	delete *(l->get(colIndex)); // release memory
	l->set(c,colIndex);
}

void Handler::setFunctionCellValue(int rowIndex,int colIndex,int row, int begin,int end,int type, LList<LList<Cell*>*>& ll)
{
	//cout << endl << "set function cell value, rowIndex=" << rowIndex << " colIndex=" << colIndex << " row=" << row << " begin=" << begin << " end=" << end<< endl;
	Cell* c = new FunctionCell(row,begin,end,type);
	LList<Cell*>* l = (*ll.get(rowIndex));
	delete *(l->get(colIndex)); // release memory
	l->set(c,colIndex);
}



void Handler::update(LList<LList<Cell*>*>& ll)
{
	while(1)
	{
		int count = checkChangeCount(ll,0);	
		
		// if count == 0 , check agein
		if(count == 0)
		{
			count = checkChangeCount(ll,0);	
			if(count == 0)
			{
				break;
			}
		}
	}// end while
}

int Handler::checkChangeCount(LList<LList<Cell*>*>& ll,int count)
{
	for(LList<Cell*>* l : ll)
		{
			for(Cell* c : *l)
			{
				// check whether is a function cell
				FunctionCell* fc = dynamic_cast<FunctionCell*>(c);
				if(fc != nullptr)
				{
					int rowIndex = fc->getRowIndex();
					int colBeg = fc->getBeg();
					int colEnd = fc->getEnd();
					double oldVal = fc->getCellValue();

					LList<Cell*>* rl = *(ll.get(rowIndex));
					LList<Cell*>::iterator ita = rl->begin();
					LList<Cell*>::iterator beg = ita,end = ita;
					while(colBeg--)
					{
						beg++;
					}
					while(colEnd-- > -1)
					{
						end++;
					}

					fc->update(beg,end); 

					int num = 0;
					if(_isnan(oldVal))
						num++;
					if(_isnan(fc->getCellValue()))
						num++;
					if(num == 1)
						count++;
					else 
						continue;
				}// end if
			}// end inner for
		}// end outer for
	return count;
}

