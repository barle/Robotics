/*
 * Box.cpp
 *
 *  Created on: Jun 28, 2015
 *      Author: colman
 */

#include "Box.h"

using namespace std;

Box::Box(Vertex *startPoint, Vertex *midPoint, Vertex *endPoint) {

	// Set the points
	this->startPnt 	= startPoint;
	this->midPnt	= midPoint;
	this->endPnt	= endPoint;

	// Calculate the last point
	this->calcedPnt = new Vertex(new Position(
			this->endPnt->getLocation()->X() - (this->midPnt->getLocation()->X() - this->startPnt->getLocation()->X()),
			this->endPnt->getLocation()->Y() - (this->midPnt->getLocation()->Y() - this->startPnt->getLocation()->Y())));
}

Box::~Box() {
	// TODO Auto-generated destructor stub
}

bool Box::isValid(Map *map)
{
	bool 	isValid = true;
	int		bigY;
	int		smallY;
	int		bigX;
	int		smallX;

	// find the bigger Y's
	if(this->startPnt->getLocation()->Y() > this->endPnt->getLocation()->Y())
	{
		bigY 	= this->startPnt->getLocation()->Y();
		smallY	= this->endPnt->getLocation()->Y();
	}
	else
	{
		bigY 	= this->endPnt->getLocation()->Y();
		smallY	= this->startPnt->getLocation()->Y();
	}

	// find the bigger X's
	if(this->startPnt->getLocation()->X() > this->endPnt->getLocation()->Y())
	{
		bigX 	= this->startPnt->getLocation()->X();
		smallX 	= this->endPnt->getLocation()->X();
	}
	else
	{
		bigX 	= this->endPnt->getLocation()->X();
		smallX 	= this->startPnt->getLocation()->X();
	}

	// Set a linear equation
	float M = (float)(bigY - smallY) / (bigX - smallX);

	// Check for each Y by the equation: X = Y/M
	for(int i = smallY; (i < bigY && isValid == true); i++)
	{
		// If the upper or lower cell is occupied, return false
		if(map->IsOccupied((int)(i/M), i) || map->IsOccupied((int)(i/M + 1), i))
		{
			isValid = false;
		}

	}

	// Check for each X by the equation: Y = MX
	for(int i = smallX; (i < bigX && isValid == true); i++)
	{
		// If the upper or lower cell is occupied, return false
		if(map->IsOccupied(i, (int)(M*i)) || map->IsOccupied(i, (int)(M*i + 1)))
		{
			isValid = false;
		}
	}

	return isValid;
}

