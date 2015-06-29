/*
 * GoTo.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#include "GoTo.h"
#include <cmath>

GoTo::GoTo(Robot *robot, Map *map, Position *goal)
	: GoToBase(robot, map, goal) {
	this->_nextGoalBehavior = NULL;
}

void GoTo::action()
{
	this->_robot->setSpeed(FORWARD_SPEED, 0);
}


bool GoTo::startCond()
{
	return !this->stopCond();
}

bool GoTo::stopCond()
{
	float deltaXInMeter,deltaYInMeter;
	float distance = getDistanceInMeter(deltaXInMeter, deltaYInMeter);
	// check if we achieved the goal within the tolerance radius
	if(distance < MAX_DIFF_RADIUS)
	{
		// we achieved the goal.. stop the robot
		this->_robot->setSpeed(0,0);
		return true;
	}

	double difYawInDegree = getDiffYawInDegree(deltaXInMeter, deltaYInMeter);
	if(difYawInDegree < MAX_DIFF_YAW && difYawInDegree > -MAX_DIFF_YAW)
	{
		return false;
	}
	//we need to change our angle...we are not in the correct direction
	this->_robot->setSpeed(0, 0);
	this->_nextBehaviors.clear();
	StraightToRight *right = new StraightToRight(this->_robot, _map, _goal, this);
	right->setNextGoal(_nextGoalBehavior);
	StraightToLeft *left = new StraightToLeft(this->_robot, _map, _goal, this);
	left->setNextGoal(_nextGoalBehavior);
	this->addNext(right);
	this->addNext(left);
	this->addNext(this);
	return true;
}

GoTo::~GoTo() {
	// TODO Auto-generated destructor stub
}
