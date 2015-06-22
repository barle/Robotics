/*
 * MoveForward.h
 *
 *  Created on: May 26, 2015
 *      Author: colman
 */

#ifndef MOVEFORWARD_H_
#define MOVEFORWARD_H_

#include "Movement.h"
#include "TurnLeft.h"
#include "TurnRight.h"
#include "Behavior.h"

class MoveForward  : public Movement{
private:
	bool checkObstacleInFront();
public:
	MoveForward(Robot *robot);
	virtual ~MoveForward();

	virtual bool startCond();
	virtual bool stopCond();
	virtual void action();
};

#endif /* MOVEFORWARD_H_ */
