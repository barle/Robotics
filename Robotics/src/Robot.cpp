/*
 * Robot.cpp
 *
 *  Created on: May 26, 2015
 *      Author: colman
 */

#include "Robot.h"

Robot::Robot(string ip, int port) : _pc(ip, port), _pp(&_pc), _lp(&_pc) {
	double x = _pp.GetXPos();
	double y = _pp.GetYPos();
	double yaw = _pp.GetYaw();

	_pos = new Position(x, y, yaw);
}

Robot::~Robot() {
	// TODO Auto-generated destructor stub
}

void Robot::setSpeed(float linear, float angular)
{
	_pp.SetSpeed(linear, angular);
}

float Robot::getX()
{
	return _pp.GetXPos();
}

float Robot::getY()
{
	return _pp.GetYPos();
}

float Robot::getYaw()
{
	return _pp.GetYaw();
}

float* Robot::getLaserScan()
{
	unsigned int samplesCount = _lp.GetCount();
	float *scan = new float[samplesCount];
	for (unsigned int i = 0; i < samplesCount; i++)
	{
		scan[i] = _lp[i];
	}
	return scan;
}

void Robot::SetDeltaValues(double &deltaX, double &deltaY, double &deltaYaw)
{
	double newX = _pp.GetXPos();
	double newY = _pp.GetYPos();
	double newYaw = _pp.GetYaw();

	// Put deltas by odometry
	if (this->_pos->X() != 0 || this->_pos->Y() != 0 || this->_pos->Yaw() != 0)
	{
		deltaX = newX - this->_pos->X();
		deltaY = newY - this->_pos->Y();
		deltaYaw = newYaw - this->_pos->Yaw();
	}
	else
	{
		deltaX = 0;
		deltaY = 0;
		deltaYaw = 0;
	}

	this->_pos->Update(newX, newY, newYaw);
}

int Robot::deg_to_index(double deg)
{
	return (deg + 120) / 0.36;
}

void Robot::read()
{
	_pc.Read();
}
