#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include "Behavior.h"

class Movement: public Behavior {
private:
	double GetDistanceByDegree(int degree);
protected:
	const double TURN_SPEED = 0.1;
	const double FORWARD_SPEED = 0.5;

	double Get0DegreeDistance();
	double Get45DegreeDistance();
	double Get315DegreeDistance();
public:
	virtual bool startCond();
	virtual bool stopCond();
	virtual void action();
	Movement(Robot *robot);
	virtual ~Movement();
};

#endif /* MOVEMENT_H_ */
