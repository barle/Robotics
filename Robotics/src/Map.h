/*
 * Map.h
 *
 *  Created on: Jun 22, 2015
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_

using namespace std;

#include <vector>

class Map {
private:
	vector<bool> grid;
	unsigned height;
	unsigned width;

public:
	Map(char* filePath);
	virtual ~Map();

	vector<bool> GetGrid();
	unsigned GetHeight();
	unsigned GetWidth();
};

#endif /* MAP_H_ */
