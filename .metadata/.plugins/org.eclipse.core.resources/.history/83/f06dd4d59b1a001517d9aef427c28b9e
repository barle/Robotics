/*
 * Main.cpp
 *
 *  Created on: May 26, 2015
 *      Author: colman
 */

#include <libplayerc++/playerc++.h>
#include <iostream>
#include "ConfigurationManager.h"
#include "Robot.h"
#include "Manager.h"
#include "Plans/ObstacleAvoidPln.h"

using namespace PlayerCc;

int main()
{
	ConfigurationManager config("/home/colman/Desktop/parameters.txt");
	Robot robot("localhost", 6665);
	ObstacleAvoidPln plan(&robot);
	Manager manager(&plan, &robot);

	manager.run();
	return 0;
}



