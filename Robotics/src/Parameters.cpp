/*
 * Parameters.cpp
 *
 *  Created on: Jun 22, 2015
 *      Author: colman
 */

#include "Parameters.h"
#include "stdlib.h"

Parameters::Parameters(const char *path) {
	ifstream file(path);
	while(file)
	{
		string line;
		getline(file, line);
		istringstream lineStream(line);
		string parameterName;
		getline(lineStream, parameterName, ':');
		string parameterValue;
		getline(lineStream, parameterValue, ':');

		parameterName = _trim(parameterName);
		parameterValue = _trim(parameterValue);

		_params[parameterName] = parameterValue;
	}

}

string Parameters::_trim(string str)
{
	// trim leading spaces
	while(str.length() &&
			(str.at(0) == ' ' || str.at(0) == 't' ||
					str.at(0) == '\r' || str.at(0) == '\n'))
	{
		str.erase(0, 1);
	}

	// trim trailing spaces
	while(str.length() &&
			(str.at(str.length()-1) == ' ' || str.at(str.length()-1) == '\t' ||
					str.at(str.length()-1) == '\r' || str.at(str.length()-1) == '\n'))
	{
		str.erase(str.length()-1, 1);
	}

	return str;
}


string Parameters::mapPath()
{
	return _params["map"];
}

Position Parameters::startLocation()
{
	string valueStr = _params["startLocation"];
	istringstream lineStream(valueStr);
	string x;
	getline(lineStream, x, ' ');
	string y;
	getline(lineStream, y, ' ');
	string yaw;
	getline(lineStream, yaw, ' ');

	_trim(x);
	_trim(y);
	_trim(yaw);

	Position robotPos(atof(x.c_str()), atof(y.c_str()), atof(yaw.c_str()));
	return robotPos;
}

Position Parameters::goal()
{
	string valueStr = _params["goal"];
	istringstream lineStream(valueStr);
	string x;
	getline(lineStream, x, ' ');
	string y;
	getline(lineStream, y, ' ');

	_trim(x);
	_trim(y);

	Position goalPos(atof(x.c_str()), atof(y.c_str()));
	return goalPos;
}

Size Parameters::robotSize()
{
	string valueStr = _params["robotSize"];
	istringstream lineStream(valueStr);
	string height;
	getline(lineStream, height, ' ');
	string width;
	getline(lineStream, width, ' ');

	_trim(height);
	_trim(width);

	Size size(atof(height.c_str()), atof(width.c_str()));
	return size;
}

double Parameters::MapResolutionCM()
{
	string value = _params["MapResolutionCM"];
	return atof(value.c_str());
}

double Parameters::GridResolutionCM()
{
	string value = _params["GridResolutionCM"];
	return atof(value.c_str());
}

Parameters::~Parameters() {
	// TODO Auto-generated destructor stub
}

