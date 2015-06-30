/*
 * GoToBase.h
 *
 *  Created on: Jun 27, 2015
 *      Author: colman
 */

#ifndef GOTOBASE_H_
#define GOTOBASE_H_

#include "Behavior.h"
#include "../Models/Position.h"
#include "../Robot.h"
#include "../Map.h"
#include <cmath>

#define MAX_DIFF_YAW 4 // Degree
#define MAX_DIFF_RADIUS 0.1  // Meter

#define ANGULAR_SPEED 0.1
#define FORWARD_SPEED 0.2
#define TURN_SPEED 0

class GoToBase : public Behavior{
protected:
	Robot *_robot;
	Map *_map;
	Position *_goal;
	GoToBase *_nextGoalBehavior;

	float getDegree(float x, float y);
	void setDeltaXYInMeter(float &deltaXInMeter, float &deltaYInMeter);
	float getDistanceInMeter(float &deltaXInMeter, float &deltaYInMeter);
	float getDiffYawInDegree(float deltaXInMeter, float deltaYInMeter);
public:
	virtual bool startCond() = 0;
	virtual bool stopCond() = 0;
	virtual void action() = 0;
	virtual Behavior *selectNext();

	void setNextGoal(GoToBase *goalBehavior);

	GoToBase(Robot *robot, Map *map, Position *goal);
	virtual ~GoToBase();
};

#endif /* GOTOBASE_H_ */
