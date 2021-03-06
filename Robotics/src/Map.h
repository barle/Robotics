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
#include <libplayerc++/playerc++.h>
#include <iostream>
#include <fstream>
#include"lodepng.h"
#include "Managers/ConfigurationManager.h"

class Map {
private:
	vector<unsigned char> _image; // the raw pixels
	vector<bool> _enlargedGrid;
	vector<bool> _mapGrid;
	unsigned _height;
	unsigned _width;
	double _gridResolution;
	double _mapResolution;

	vector<bool> loadMap(const char* fileName, unsigned& width, unsigned& height);

public:
	Map(ConfigurationManager *config);
	virtual ~Map();

	vector<bool> GetGrid();
	unsigned GetHeight();
	unsigned GetWidth();
	double GetGridResolution();
	double GetMapResolution();

	// Converters:
	float convertDegreeToRadian(float degree);
	float convertRadianToDegree(float radian);

	float convertPixelToMeter(float inPixel);
	float convertMeterToPixel(float inMeter);

	bool IsOccupied(int x, int y);
	bool IsOccupiedInOriginalMap(int x, int y);
};

#endif /* MAP_H_ */
