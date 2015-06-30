/*
 * Line.h
 *
 *  Created on: Jun 28, 2015
 *      Author: colman
 */

#ifndef LINE_H_
#define LINE_H_

#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

#include "Vertex.h"
#include <stdlib.h>

using namespace std;

class Line {
public:
	Vertex 	*startPnt;
	Vertex	*endPnt;
	int		direction;
	int		len;

	Line(Vertex *startPoint, Vertex *endPoint);
	virtual ~Line();
};


#endif /* LINE_H_ */
