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

vector<Vertex*> WaypointManager::mergeStraightPoints(vector<Vertex*> path)
{
	// Declare variables
	vector<Vertex*> fixedPath;

	int outerCounter = 0;
	int innerCounter = 1;
	bool firstCompere = true;
	bool isLastRun = false;
	int lineDirection;

	// Add the first vertex
	fixedPath.push_back(path[0]);

	// Merge points in the same straight line
	while(outerCounter < path.size())
	{
		while(innerCounter < path.size())
		{
			// If this is the fist comparison, save the direction
			if(firstCompere && innerCounter != path.size() -1)
			{
				// Get the direction of the line
				lineDirection = this->areOnSameLine(path[outerCounter], path[innerCounter]);
				firstCompere = false;

				// Promote the inner counter
				innerCounter++;
			}

			// Check if not on the same line
			else if(lineDirection != areOnSameLine(path[outerCounter], path[innerCounter]) && !isLastRun)
			{

				// Add the vertex
				fixedPath.push_back(path[innerCounter - 1]);

				// Reset the flag
				firstCompere = true;

				// promote the outer counter to the inner position
				outerCounter = innerCounter - 1;

				// Mark last run
				if (innerCounter == path.size() -1)
				{
					isLastRun = true;
				}
			}

			// If we get to the last cell
			else if (innerCounter == path.size() -1)
			{
				// Add the vertex
				fixedPath.push_back(path[innerCounter]);

				// Set the counters to quit the loop
				innerCounter = path.size();
				outerCounter = path.size();
			}
			else
			{

				// Promote the inner counter
				innerCounter++;
			}
		}
	}

	// Return the fixed path
	return fixedPath;
}

int  WaypointManager::areOnSameLine(Vertex *first, Vertex *second)
{
	if(first->getLocation()->X() == second->getLocation()->X())
	{
		return HORIZONTAL;
	}
	else if (first->getLocation()->Y() == second->getLocation()->Y())
	{
		return VERTICAL;
	}
	else
	{
		return NONE;
	}
}

vector<Line*> WaypointManager::getLinesVector(vector<Vertex*> path)
{
	vector<Line*> lineVector;
	for(int i=1 ;i < path.size(); i++)
	{
		lineVector.push_back(new Line(path[i - 1], path[i]));
	}

	return lineVector;
}

vector<Box*> WaypointManager::getBoxesVector(vector<Vertex*> path)
{
	vector<Box*> boxVector;

	// Divide by 3 to prevent overflow
	for(int i=0; i < (int)(path.size() / 3); i++)
	{
		int idx = i*3;
		boxVector.push_back(new Box(path[idx], path[idx + 1], path[idx + 2]));
	}

	return boxVector;
}

vector<Vertex*> WaypointManager::getRemainingVertexes(vector<Vertex*> path)
{
	vector<Vertex*> remainingVertexes;
	int initSize;

	// Set the initial size
	if((int)(path.size() % 3) == 1)
	{
		initSize = path.size() - 1;
	}
	else if((int)(path.size() % 3) == 2)
	{
		initSize = path.size() - 2;
	}
	else
	{
		initSize = path.size();
	}

	for(int i = initSize; i < path.size(); i++)
	{
		remainingVertexes.push_back(path[i]);
	}

	return remainingVertexes;
}

vector<Vertex*> WaypointManager::optimizePath(vector<Vertex*> path)
{
	int mergeCount = 1;
	int numOfRounds = 0;
	vector<Box*> boxVector;

	// Merge straight lines
	vector<Vertex*> tmpPath = this->mergeStraightPoints(path);

	// Run until finished with all the merges
	while(mergeCount != 0 && numOfRounds < MAX_OPTIMIZE_LOOP)
	{
		// Get Lines vector
		boxVector = this->getBoxesVector(tmpPath);

		// Gets the last points who didn't perform a box
		vector<Vertex*> remainingVertexes = this->getRemainingVertexes(tmpPath);

		// Reset the variables
		numOfRounds++;
		mergeCount = 0;
		tmpPath.clear();

		// For each box, try to unite it
		for(int i=0; i < boxVector.size(); i++)
		{
			// If the merge was successful, don't add the mid point
			if(boxVector[i]->isValid(this->_map))
			{
				tmpPath.push_back(boxVector[i]->startPnt);

				// Record the merge
				mergeCount++;
			}
			else
			{
				tmpPath.push_back(boxVector[i]->startPnt);
				tmpPath.push_back(boxVector[i]->midPnt);
			}
		}

		// Add the last point
		tmpPath.push_back(boxVector[boxVector.size() - 1]->endPnt);

		// Add the vertexes without the box
		for(int i=0; i < remainingVertexes.size(); i++)
		{
			tmpPath.push_back(remainingVertexes[i]);
		}

		// Recreate the Boxes vector with the new path
		boxVector.clear();
		remainingVertexes.clear();
	}
	return tmpPath;
}