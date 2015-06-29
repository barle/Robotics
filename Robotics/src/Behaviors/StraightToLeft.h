/*
 * StraightToLeft.h
 *
 *  Created on: Jun 27, 2015
 *      Author: colman
 */

#ifndef STRAIGHTTOLEFT_H_
#define STRAIGHTTOLEFT_H_

#include "GoToBase.h"

class StraightToLeft : public GoToBase{
private:
	GoToBase *_goalBehavior;
public:
	virtual bool startCond();
	virtual bool stopCond();
	virtual void action();

	StraightToLeft(Robot *robot, Map *map, Position *goal, GoToBase *goalBehavior);
	virtual ~StraightToLeft();
};

#endif /* STRAIGHTTOLEFT_H_ */
