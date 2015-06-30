/*
 * Box.h
 *
 *  Created on: Jun 28, 2015
 *      Author: colman
 */

#ifndef BOX_H_
#define BOX_H_

#define MAX_POINTS 2
#define MID_POINT_DELTA 15

#include "Vertex.h"
#include "Line.h"
#include "Position.h"
#include "../Map.h"

using namespace std;

class Box {
public:
	Vertex	*startPnt;
	Vertex	*endPnt;
	Vertex	*midPnt;
	Vertex	*calcedPnt;

	bool isValid(Map *map);
	Box(Vertex *startPoint, Vertex *midPoint, Vertex *endPoint);
	virtual ~Box();
};

#endif /* BOX_H_ */
