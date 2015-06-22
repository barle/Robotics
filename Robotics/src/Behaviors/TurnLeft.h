#ifndef TURNLEFT_H_
#define TURNLEFT_H_

#include "Movement.h"

class TurnLeft  : public Movement {
public:
	virtual bool startCond();
	virtual bool stopCond();
	virtual void action();
	TurnLeft(Robot *robot);
	virtual ~TurnLeft();
};


#endif /* TURNLEFT_H_ */
