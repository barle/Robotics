/*
 * Robot.h
 *
 *  Created on: May 26, 2015
 *      Author: colman
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include <libplayerc++/playerc++.h>
#include <string>
#include "Models/Position.h"

using namespace PlayerCc;
using namespace std;

#define MAP_X_SIZE 40
#define MAP_Y_SIZE 20

class Robot {
private:
	PlayerClient _pc;
	Position2dProxy _pp;
	LaserProxy _lp;
	PlayerClient *_dummyPainter; //this is a dummy client for drawing
	Graphics2dProxy *_gp;

	Position *_lastPosInPixel;
	Position *_startInPixel;
	int _mapHeightInPixel;
	int _mapWidthInPixel;
	double _mapResolutionInMeters;

public:
	Robot(string ip, int port, Position *startInPixel, int mapHeightInPixel, int mapWidthInPixel, double mapResolutionInMeters);
	virtual ~Robot();

	void SetDeltaValues(double &deltaXInPixel, double &deltaYInPixel, double &deltaYawInDegree);
	void setSpeed(float linear, float angular);
	float getX();
	float getY();
	float getYaw();

	// Converters:
	float convertDegreeToRadian(float degree);
	float convertRadianToDegree(float radian);

	float convertPixelToMeter(float inPixel);
	float convertMeterToPixel(float inMeter);

	float* getLaserScan();
	int deg_to_index(double deg);

	void read();

	void drawPoint(float x, float y, float size, int red = 255, int blue = 0, int green = 0);
};

#endif /* ROBOT_H_ */
