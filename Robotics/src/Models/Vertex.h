/*
 * Vertex.h
 *
 *  Created on: Jun 24, 2015
 *      Author: colman
 */

#ifndef VERTEX_H_
#define VERTEX_H_

#include <vector>
#include "Position.h"

using namespace std;

class Vertex {
private:
	double _h;
	double _g;
	Position *_location;
	vector<Vertex*> _adj;
public:
	void setH(double h);
	void setG(double g);

	double getH(); // approximate cost to the target(heuristic function)
	double getG(); // cost from the beginning
	double getF(); // approximate total cost to the target (h+g)

	Position* getLocation(); // the location of the vertex in the map

	vector<Vertex*> getAdj(); // the adjacent list of this vertex
	void addNeighbor(Vertex *neighbor);

	Vertex(Position *location);
	virtual ~Vertex();
};

#endif /* VERTEX_H_ */
