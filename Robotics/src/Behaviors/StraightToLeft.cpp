/*
 * StraightToLeft.cpp
 *
 *  Created on: Jun 27, 2015
 *      Author: colman
 */

#include "StraightToLeft.h"

StraightToLeft::StraightToLeft(Robot *robot, Map *map, Position *goal, GoToBase *goalBehavior)
	: GoToBase(robot, map, goal)
{
	this->_goalBehavior = goalBehavior;
}

void StraightToLeft::action()
{
	this->_robot->setSpeed(TURN_SPEED, ANGULAR_SPEED); // turn left
}

bool StraightToLeft::stopCond()
{
	float deltaXInMeter,deltaYInMeter;
	setDeltaXYInMeter(deltaXInMeter,deltaYInMeter);
	float difYawInDegree = getDiffYawInDegree(deltaXInMeter, deltaYInMeter);


	if(difYawInDegree < MAX_DIFF_YAW && difYawInDegree > -MAX_DIFF_YAW)
	{ //this mean the goal is in front of the robot so we stop turning...
		this->_robot->setSpeed(0, 0);
		this->_nextBehaviors.clear();
		this->addNext(this->_goalBehavior);
		return true;
	}
	else if((difYawInDegree >= -180 && difYawInDegree <= 0) || (difYawInDegree >= 180 && difYawInDegree <= 360)) // turn left needed
	{ // this mean the goal is on the left of the robot so we don't stop the condition...
		return false;
	}
	this->_robot->setSpeed(0,0);
	this->_nextBehaviors.clear();
	this->addNext(_goalBehavior);
	return true;
}

bool StraightToLeft::startCond()
{
	return !this->stopCond();
}

StraightToLeft::~StraightToLeft() {
	// TODO Auto-generated destructor stub
}

