/*
 * GoTo.h
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#ifndef GOTO_H_
#define GOTO_H_

#include "GoToBase.h"
#include "StraightToLeft.h"
#include "StraightToRight.h"

class GoTo : public GoToBase{
public:
	virtual bool startCond();
	virtual bool stopCond();
	virtual void action();

	GoTo(Robot *robot, Map *map, Position *goal);
	virtual ~GoTo();
};

#endif /* GOTO_H_ */
