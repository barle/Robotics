/*
 * Main.cpp
 *
 *  Created on: May 26, 2015
 *      Author: colman
 */

#include <libplayerc++/playerc++.h>
#include <iostream>
#include "Managers/ConfigurationManager.h"
#include "Managers/LocalizationManager.h"
#include "Robot.h"
#include "Managers/Manager.h"

#include "Plans/PathPlanner.h"
#include "Models/Vertex.h"
#include "Models/Position.h"
#include <cmath>

using namespace PlayerCc;

int main()
{
	ConfigurationManager config("/home/colman/Desktop/parameters.txt");
	Map map(&config);
	Robot robot("localhost", 6665, config.getStartLocation(), &map);
	PathPlanner plan(&robot, &map, config.getStartLocation(), config.getGoal());
	LocalizationManager loc(&map, &robot);
	Manager manager(&plan, &loc, &robot, &map);

	manager.run();
	return 0;
}



