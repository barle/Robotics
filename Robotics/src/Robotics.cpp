/*
 * Main.cpp
 *
 *  Created on: May 26, 2015
 *      Author: colman
 */

#include <libplayerc++/playerc++.h>
#include <iostream>
#include "Managers/ConfigurationManager.h"
#include "Robot.h"
#include "Managers/Manager.h"
#include "Plans/ObstacleAvoidPln.h"

#include "Managers/PathPlanner.h"
#include "Models/Vertex.h"
#include "Models/Position.h"
#include <cmath>

using namespace PlayerCc;

void printPath(vector<Vertex*> path)
{
	cout << "path:" << endl;
	Position *last = path[0]->getLocation();
	double sum = 0;
	for(unsigned int i = 0; i < path.size(); i++)
	{
		Position* loc = path[i]->getLocation();
		cout << loc->X() << "," << loc->Y() << endl;
		sum += sqrt(pow(loc->X()-last->X(),2) + pow(loc->Y()-last->Y(),2));
		last = loc;
	}
	cout<< sum<<endl;
}

void testPathPlanner(ConfigurationManager *config)
{
	Map map(config->getMapPath().c_str());

	PathPlanner pathPlanner(&map);
	Vertex v1(new Position(0,0));
	Vertex v2(new Position(1,1));
	Vertex v3(new Position(2,2));
	Vertex v4(new Position(1,4));
	Vertex v5(new Position(2,1));

	v1.addNeighbor(&v2);
	v2.addNeighbor(&v3);
	v4.addNeighbor(&v2);
	//v2.addNeighbor(&v5);
	//v3.addNeighbor(&v5);
	v1.addNeighbor(&v3);
	v3.addNeighbor(&v4);
	v4.addNeighbor(&v5);
	//v1.addNeighbor(&v5);

	Position *start = config->getStartLocation();
	Position *goal = config->getGoal();
	vector<Vertex*> bestWay = pathPlanner.AStar(start, goal);
	printPath(bestWay);
}

int main()
{
	ConfigurationManager config("/home/colman/Desktop/parameters.txt");

	testPathPlanner(&config); // todo: remove this!

	Robot robot("localhost", 6665);
	ObstacleAvoidPln plan(&robot);
	Manager manager(&plan, &robot);

	manager.run();
	return 0;
}



