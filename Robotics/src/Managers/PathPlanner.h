/*
 * PathPlanner.h
 *
 *  Created on: Jun 23, 2015
 *      Author: colman
 */

#ifndef PATHPLANNER_H_
#define PATHPLANNER_H_

#include <vector>
#include <map>
#include <queue>
#include "../Models/Vertex.h"
#include "AStarComparison.h"

using namespace std;

class PathPlanner {
public:
	PathPlanner();
	virtual ~PathPlanner();

	vector<Vertex*> AStar(Vertex* start, Vertex* goal);
	vector<Vertex*> reconstructPath(map<Vertex*,Vertex*> cameFrom, Vertex *current);
	double distBetween(Vertex *start, Vertex *goal);
};

#endif /* PATHPLANNER_H_ */
