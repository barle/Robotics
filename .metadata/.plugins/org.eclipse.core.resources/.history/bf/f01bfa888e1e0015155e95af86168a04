/*
 * StraightToRight.h
 *
 *  Created on: Jun 27, 2015
 *      Author: colman
 */

#ifndef STRAIGHTTORIGHT_H_
#define STRAIGHTTORIGHT_H_

#include "GoToBase.h"

class StraightToRight : public GoToBase{
private:
	GoToBase *_goalBehavior;
public:
	virtual bool startCond();
	virtual bool stopCond();
	virtual void action();

	StraightToRight(Robot *robot, Position *goal, GoToBase *goalBehavior);
	virtual ~StraightToRight();
};

#endif /* STRAIGHTTORIGHT_H_ */
