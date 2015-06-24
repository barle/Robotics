/*
 * PathPlanner.cpp
 *
 *  Created on: Jun 23, 2015
 *      Author: colman
 */

#include "PathPlanner.h"
#include <cmath>

using namespace std;

PathPlanner::PathPlanner() {
	// TODO Auto-generated constructor stub

}

PathPlanner::~PathPlanner() {
	// TODO Auto-generated destructor stub
}

// A* algorithm
vector<Vertex*> PathPlanner::AStar(Vertex *start, Vertex *goal)
{
	map<Vertex*, Vertex*> cameFrom; // save for each vertex we visit the vertex we came from
	priority_queue<Vertex*,vector<Vertex*>,AStarComparison> openset;

	// use this maps to simplify the existence check of any vertex
	map<Vertex*,bool> opensetMap;
	map<Vertex*,bool> closedsetMap;

	openset.push(start);
	opensetMap[start] = true;

	start->setG(0);
	start->setH(distBetween(start,goal));

	while(!openset.empty())
	{
		Vertex* current = openset.top();
		if(current == goal)
			return reconstructPath(cameFrom, goal);

		// remove the current vertex from the open set
		openset.pop();
		opensetMap[current] = false;
		// add the current vertex to the closed set
		closedsetMap[current] = true;

		// visit all neighbors
		for(unsigned int i=0; i < current->getAdj().size(); i++)
		{
			Vertex *neighbor = current->getAdj()[i];
			if(closedsetMap[neighbor])
				continue;
			double tentativeGScore = current->getG() + distBetween(current,neighbor);
			if(!opensetMap[neighbor] || tentativeGScore < neighbor->getG())
			{
				cameFrom[neighbor] = current;
				neighbor->setG(tentativeGScore);
				neighbor->setH(distBetween(neighbor,goal));
				if(!opensetMap[neighbor])
				{
					openset.push(neighbor);
					opensetMap[neighbor] = true;
				}
			}
		}
	}
	return vector<Vertex*>(); // no path found...
}

// this is the heuristic function for the A* algorithm
double PathPlanner::distBetween(Vertex *start, Vertex *goal)
{
	Position *startLocation = start->getLocation();
	Position *goalLocation = goal->getLocation();

	double a2 = pow(goalLocation->X() - startLocation->X(),2);
	double b2 = pow(goalLocation->Y() - startLocation->Y(),2);
	double dist = sqrt(a2 + b2);
	return dist;
}

vector<Vertex*> PathPlanner::reconstructPath(map<Vertex*,Vertex*> cameFrom, Vertex *current)
{
	vector<Vertex*> totalPath;
	while(current)
	{
		totalPath.push_back(current);
		current = cameFrom[current];
	}
	return totalPath;
}
