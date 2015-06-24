/*
 * PathPlanner.cpp
 *
 *  Created on: Jun 23, 2015
 *      Author: colman
 */

#include "PathPlanner.h"
#include <cmath>

using namespace std;

PathPlanner::PathPlanner(Map *map)
{
	vector<bool> mapGrid = map->GetGrid();
	_graphHeight = map->GetHeight();
	_graphWidth = map->GetWidth();

	_graph = convertMapToGraph(mapGrid, _graphHeight, _graphWidth);
}


// A* algorithm
vector<Vertex*> PathPlanner::AStar(Position *start, Position *goal)
{
	Vertex* startVertex = _graph[(_graphWidth*start->Y()) + start->X()];
	Vertex* goalVertex = _graph[(_graphWidth*goal->Y()) + goal->X()];
	map<Vertex*, Vertex*> cameFrom; // save for each vertex we visit the vertex we came from
	priority_queue<Vertex*,vector<Vertex*>,AStarComparison> openset;

	// use this maps to simplify the existence check of any vertex
	map<Vertex*,bool> opensetMap;
	map<Vertex*,bool> closedsetMap;

	openset.push(startVertex);
	opensetMap[startVertex] = true;

	startVertex->setG(0);
	startVertex->setH(distBetween(startVertex,goalVertex));

	while(!openset.empty())
	{
		Vertex* current = openset.top();
		if(current == goalVertex)
			return reconstructPath(cameFrom, goalVertex);

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
				neighbor->setH(distBetween(neighbor,goalVertex));
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

vector<Vertex*> PathPlanner::convertMapToGraph(vector<bool> mapGrid, int height, int width)
{
	int size = (height*width);
	vector<Vertex*> graph(size);
	for(int i = 0; i < height ; i++)
	{
		for(int j = 0; j < width; j++)
		{
			Vertex *v = new Vertex(new Position(j,i));
			graph[(i* width) + j] = v;
		}
	}

	//fill neighbors
	for(int i = 0; i< height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int currentIndex = (width * i) + j;
			int neighborIndex = (width * (i-1)) + j; // upper cell
			addNeighborIfPossible(currentIndex, neighborIndex, size, &mapGrid, &graph);
			neighborIndex = (width * (i+1)) + j; // bottom cell
			addNeighborIfPossible(currentIndex, neighborIndex, size, &mapGrid, &graph);
			neighborIndex = (width * i) + j + 1; // right cell
			addNeighborIfPossible(currentIndex, neighborIndex, size, &mapGrid, &graph);
			neighborIndex = (width * (i-1)) + j - 1; // left cell
			addNeighborIfPossible(currentIndex, neighborIndex, size, &mapGrid, &graph);
		}
	}

	return graph;
}

void PathPlanner::addNeighborIfPossible(int currentIndex, int neighborIndex, int size, vector<bool> *mapGrid, vector<Vertex*> *graph)
{
	if(neighborIndex > 0 &&
		neighborIndex < size &&
		(*mapGrid)[neighborIndex] == 0)
	{
		(*graph)[currentIndex]->addNeighbor((*graph)[neighborIndex]);
	}
}


PathPlanner::~PathPlanner() {
	// TODO Auto-generated destructor stub
}
