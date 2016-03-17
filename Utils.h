#pragma once

#include <string>
#include <sstream>
#include <limits>
using namespace std;

class Utils
{
public:

	//static const double NaN;

	template<class T>
	static string toString(T t);
	
	template<class T>
	static bool isAbleToType(string& str);

	template<class T>
	static T toType(string& str);
};

//const double Utils::NaN = numeric_limits<double>::quiet_NaN();

/*
	convert T to string
*/
template<class T>
string Utils::toString(T t)
{
	ostringstream oss;
	oss << t;
	return oss.str();
}

/*
	check wheter str is able to convert to Type T
	for example:  str = "12.3";
	Utils::isAbleToType<double>(str)  will return true;
	Utils::isAbleToType<int>(str)  will return false;
*/
template<class T>
bool Utils::isAbleToType(string& str)
{
	istringstream iss(str);
	T t;
	string s;
	return (iss >> t) && !(iss >> s);
}

/*
	convert str to type T
*/
template<class T>
T Utils::toType(string& str)
{
	istringstream iss(str);
	T t;
	iss >> t;
	return t;
}
