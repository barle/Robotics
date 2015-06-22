#ifndef PLAN_H_
#define PLAN_H_

#include <vector>
#include "../Robot.h"
#include "../Behaviors/Behavior.h"

class Plan {
private:
	Robot *_robot;

protected:
	vector<Behavior *> _behaviors;

public:
	Plan(Robot *robot);
	virtual ~Plan();
	virtual Behavior *getStartBehavior() = 0;
};

#endif /* PLAN_H_ */
