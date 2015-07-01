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
#include "Map.h"

using namespace PlayerCc;
using namespace std;

class Robot {
private:
	PlayerClient _pc;
	Position2dProxy _pp;
	LaserProxy _lp;
	PlayerClient *_dummyPainter; //this is a dummy client for drawing
	Graphics2dProxy *_gp;

	Map *_map;
	Position *_lastPosInPixel;
	Position *_startInPixel;

public:
	Robot(string ip, int port, Position *startInPixel, Map *map);
	virtual ~Robot();

	void setOdometry(Position *posInPixel);
	void SetDeltaValues(double &deltaXInPixel, double &deltaYInPixel, double &deltaYawInDegree);
	void setSpeed(float linear, float angular);
	void ClearParticles();
	float getX();
	float getY();
	float getYaw();

	float* getLaserScan();
	int deg_to_index(double deg);

	void read();

	void drawPoint(float x, float y, float size, int red = 255, int blue = 0, int green = 0);
};

#endif /* ROBOT_H_ */
