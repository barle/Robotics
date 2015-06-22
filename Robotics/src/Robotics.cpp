/*
 * Main.cpp
 *
 *  Created on: May 26, 2015
 *      Author: colman
 */

#include <libplayerc++/playerc++.h>
#include <iostream>
#include "Robot.h"
#include "Manager.h"
#include "Plans/ObstacleAvoidPln.h"

using namespace PlayerCc;

int main()
{
	Robot robot("localhost", 6665);
	ObstacleAvoidPln plan(&robot);
	Manager manager(&plan, &robot);

	manager.run();
	return 0;
}


