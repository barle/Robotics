/*
 * AStarComparison.h
 *
 *  Created on: Jun 24, 2015
 *      Author: colman
 */

#ifndef ASTARCOMPARISON_H_
#define ASTARCOMPARISON_H_

#include "../Models/Vertex.h"

class AStarComparison {
public:
	bool operator() (Vertex*& first, Vertex*& second) const;

	AStarComparison();
	virtual ~AStarComparison();
};

#endif /* ASTARCOMPARISON_H_ */