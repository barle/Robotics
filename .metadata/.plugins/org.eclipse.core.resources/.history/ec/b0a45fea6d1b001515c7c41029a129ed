#ifndef CONFIGURATIONMANAGER_H_
#define CONFIGURATIONMANAGER_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include "../Models/Position.h"
#include "../Models/Size.h"

using namespace std;

class ConfigurationManager {
private:
	map<string, string> _params;
	string  _trim(string str);
public:
	string getMapPath();
	Position* getStartLocation();
	Position* getGoal();
	Size* getRobotSize();
	double getMapResolutionCM();
	double getGridResolutionCM();
	ConfigurationManager(const char *path);
	virtual ~ConfigurationManager();
};

#endif /* CONFIGURATIONMANAGER_H_ */
