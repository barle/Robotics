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
#include "../Models/Position.h"
#include "../Map.h"
#include "../Managers/WaypointManager.h"

#include "../Behaviors/GoTo.h"
#include "AStarComparison.h"
#include "Plan.h"
#include "libplayerc++/playerc++.h"

using namespace std;

class PathPlanner : public Plan{
private:
	Graphics2dProxy *_gp;
	PlayerClient *_pc;

	vector<Vertex*> _graph;
	int _graphHeight;
	int _graphWidth;

	vector<Vertex*> reconstructPath(map<Vertex*,Vertex*> cameFrom, Vertex *current);
	double distBetween(Vertex *start, Vertex *goal);
	vector<Vertex*> convertMapToGraph(vector<bool> mapGrid, int height, int width);
	void addNeighborIfPossible(int currentIndex, int neighborIndex, int size, vector<bool> *mapGrid, vector<Vertex*> *graph);

	void print(vector<Vertex*> path);
public:
	PathPlanner(Robot *robot, Map *map, Position *start, Position* goal);
	virtual ~PathPlanner();
	virtual Behavior *getStartBehavior();

	vector<Vertex*> AStar(Position* start, Position* goal);
};

#endif /* PATHPLANNER_H_ */
