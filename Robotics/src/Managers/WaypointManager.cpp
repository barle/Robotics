/*
 * WaypointManager.cpp
 *
 *  Created on: Jun 25, 2015
 *      Author: colman
 */

#include "WaypointManager.h"

using namespace std;

WaypointManager::WaypointManager(Map *map) {
	_map = map;
}

WaypointManager::~WaypointManager() {
	// TODO Auto-generated destructor stub
}

vector<Vertex*> WaypointManager::optimizePath(vector<Vertex*> path)
{
	bool hasChanged = true;
	while(hasChanged){
		hasChanged = false;
		vector<Vertex*> optimizedPath;
		unsigned int i;
		for(i=0; i<path.size()-2;i++){
			Vertex* v1 = path[i];
			Vertex* v2 = path[i+1]; // not in used just for understanding
			Vertex* v3 = path[i+2];

			optimizedPath.push_back(v1);

			bool isClear = IsClearPath(v1,v3);
			if(isClear){
				i++;//skip the v2
				hasChanged = true;
			}
		}
		if(i==path.size()-2){ //push the one before last vertex
			optimizedPath.push_back(path[path.size()-2]);
		}
		optimizedPath.push_back(path[path.size()-1]); // push the last vertex
		path = optimizedPath;
	}

	return path;
}

bool WaypointManager::IsClearPath(Vertex *v1, Vertex *v2)
{
	bool isClear = true;

	int x1 = v1->getLocation()->X();
	int x2 = v2->getLocation()->X();
	int y1 = v1->getLocation()->Y();
	int y2 = v2->getLocation()->Y();

	int distance = sqrt(pow(x1-x2,2) + pow(y1-y2,2));
	if(distance > MIN_DIST_TO_MERGE){
		return false;
	}

	int bigX,smallX;
	// find the bigger X's
	if(x1 > x2)
	{
		bigX 	= x1;
		smallX 	= x2;
	}
	else
	{
		bigX 	= x2;
		smallX 	= x1;
	}
	int bigY,smallY;
	// find the bigger Y's
	if(y1 > y2)
	{
		bigY 	= y1;
		smallY 	= y2;
	}
	else
	{
		bigY 	= y2;
		smallY 	= y1;
	}

	// Set a linear equation
	float a = (float)(y2 - y1) / (x2 - x1);
	for(double i = smallX; (i < bigX && isClear); i+=0.2)
	{
		int y = ((float)a*i) -((float)a*x1) + y1;
		if(_map->IsOccupied(i, y)) {
			isClear = false;
		}

	}
	return isClear;
}
