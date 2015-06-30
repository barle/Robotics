/*
 * Line.cpp
 *
 *  Created on: Jun 28, 2015
 *      Author: colman
 */

#include "Line.h"

using namespace std;

Line::Line(Vertex *startPoint, Vertex *endPoint) {
	this->startPnt	= startPoint;
	this->endPnt	= endPoint;

	// Get direction and length
	if(startPoint->getLocation()->X() != endPoint->getLocation()->X())
	{
		this->len = abs(startPoint->getLocation()->X() - endPoint->getLocation()->X());
		if (startPoint->getLocation()->X() < endPoint->getLocation()->X())
		{
			this->direction = RIGHT;
		}
		else
		{
			this->direction = LEFT;
		}
	}
	else
	{
		this->len = abs(startPoint->getLocation()->Y() - endPoint->getLocation()->Y());
		if (startPoint->getLocation()->Y() < endPoint->getLocation()->Y())
		{
			this->direction = UP;
		}
		else
		{
			this->direction = DOWN;
		}
	}
}

Line::~Line() {
	// TODO Auto-generated destructor stub
}

