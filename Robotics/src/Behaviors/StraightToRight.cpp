/*
 * StraightToRight.cpp
 *
 *  Created on: Jun 27, 2015
 *      Author: colman
 */

#include "StraightToRight.h"

StraightToRight::StraightToRight(Robot *robot, Map *map, Position *goal, GoToBase *goalBehavior)
	: GoToBase(robot, map, goal)
{
	this->_goalBehavior = goalBehavior;
}

void StraightToRight::action()
{
	this->_robot->setSpeed(TURN_SPEED, - ANGULAR_SPEED); // turn right
}

bool StraightToRight::stopCond()
{
	float deltaXInMeter,deltaYInMeter;
	setDeltaXYInMeter(deltaXInMeter,deltaYInMeter);
	float difYawInDegree = getDiffYawInDegree(deltaXInMeter, deltaYInMeter);


	if(difYawInDegree < MAX_DIFF_YAW && difYawInDegree > -MAX_DIFF_YAW)
	{ //this mean the goal is in front of the robot so we stop turning...
		this->_nextBehaviors.clear();
		this->addNext(this->_goalBehavior);
		this->_robot->setSpeed(0, 0);
		return true;
	}
	else if((difYawInDegree >= -360 && difYawInDegree <= -180) || (difYawInDegree >= 0 && difYawInDegree <= 180)) // turn right needed
	{ // this mean the goal is on the right of the robot so we don't stop the condition...
		return false;
	}
	this->_nextBehaviors.clear();
	this->addNext(_goalBehavior);
	this->_robot->setSpeed(0,0);
	return true;
}

bool StraightToRight::startCond()
{
	return !this->stopCond();
}

StraightToRight::~StraightToRight() {
	// TODO Auto-generated destructor stub
}

