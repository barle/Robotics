/*
 * AStarComparison.cpp
 *
 *  Created on: Jun 24, 2015
 *      Author: colman
 */

#include "AStarComparison.h"

bool AStarComparison::operator() (Vertex*& first, Vertex*& second) const
{
	return (first->getF()>second->getF());
}

AStarComparison::AStarComparison() {
	// TODO Auto-generated constructor stub

}

AStarComparison::~AStarComparison() {
	// TODO Auto-generated destructor stub
}

