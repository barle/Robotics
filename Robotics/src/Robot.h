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

class Robot {
private:
	PlayerClient _pc;
	Position2dProxy _pp;
	LaserProxy _lp;
	Position *_pos;

public:
	Robot(string ip, int port);
	virtual ~Robot();

	void SetDeltaValues(double &deltaX, double &deltaY, double &deltaYaw);
	void setSpeed(float linear, float angular);
	float getX();
	float getY();
	float getYaw();

	float* getLaserScan();
	int deg_to_index(double deg);

	void read();
};

#endif /* ROBOT_H_ */
