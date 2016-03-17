#include <iostream>
#include <vector>
#include <sstream>

#include "Cell.h"
#include "NumericCell.h"
#include "StringCell.h"
#include "FunctionCell.h"
#include "list.h"
#include "Handler.h"
#include "Utils.h"
using namespace std;


LList<LList<Cell*>*> ll; // store spreadsheet data
int width;  // cols
int height; // rows

int main(int argc, char** argv)
{
	// check arg amount
	if(argc < 3)
	{
		cout << "not enough args" << endl;
		return 1;
	}

	// read width and height from command line
	try
	{
		width = stoi(string(argv[1]));  //columns
		height = stoi(string(argv[2])); //rows
		
		// check positive
		if(width <= 0 || height <= 0)
		{
			cout << "width and height need to be positive" << endl;
			return 1;
		}
	}
	catch(exception e)  // bad cast
	{
		cout << "Got bad values for width and height" << endl;
		return 1;
	}
	
	// initialize ll
	for(int i=0;i<height;i++)
	{
		LList<Cell*>* l = new LList<Cell*>;
		Cell* ptr = nullptr;
		for(int j=0;j<width;j++)
		{
			l->push_back(ptr);
		}
		ll.push_back(l);
	}

	//cout << "width=" << width << " height=" << height << endl;
	Handler::width = width;
	Handler::height = height;
	// read command
	string command;
	vector<string> paraVec; // split the command and store the words into vector

	while(getline(cin, command))
	{
		if(Handler::checkValidate(command,height,width,paraVec,ll))
		{
			Handler::processCommand(command,paraVec,ll);
			// if it is quit command
			if(paraVec[0] == Handler::COMMAND_QUIT)
			{
				return 0;
			}
		}
		paraVec.clear(); // clear paraVec
	}

	
}

