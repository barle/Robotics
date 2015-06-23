/*
 * Parameters.h
 *
 *  Created on: Jun 22, 2015
 *      Author: colman
 */

#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include "Models/Position.h"
#include "Models/Size.h"

using namespace std;

class Parameters {
private:
	map<string, string> _params;
	string  _trim(string str);
public:
	string mapPath();
	Position startLocation();
	Position goal();
	Size robotSize();
	double MapResolutionCM();
	double GridResolutionCM();
	Parameters(const char *path);
	virtual ~Parameters();
};

#endif /* PARAMETERS_H_ */
