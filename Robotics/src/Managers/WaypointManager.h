/*
 * WaypointManager.h
 *
 *  Created on: Jun 25, 2015
 *      Author: colman
 */

#ifndef WAYPOINTMANAGER_H_
#define WAYPOINTMANAGER_H_

// Define consts
#define HORIZONTAL 1
#define VERTICAL 2
#define NONE 3
#define MIN_DIST_TO_MERGE 20

#include <vector>
#include <queue>
#include "../Models/Vertex.h"
#include "../Models/Position.h"
#include "../Map.h"

using namespace std;

class WaypointManager {

private:
	bool IsClearPath(Vertex *v1, Vertex *v2);
	Map *_map;

public:
	WaypointManager(Map *map);
	virtual ~WaypointManager();
	vector<Vertex*> optimizePath(vector<Vertex*> path);
};


#endif /* WAYPOINTMANAGER_H_ */
