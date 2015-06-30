#include "MoveForward.h"

bool MoveForward::startCond() {
	return true;
}

bool MoveForward::stopCond() {
	// Calculate all distances for moving
	double forwardDistance = Get0DegreeDistance();
	double rightDistance = Get45DegreeDistance();
	double leftDistance = Get315DegreeDistance();

	// make sure we can move forward or distance wasn't set yet.

	if ((forwardDistance > 1 && rightDistance > 1 && leftDistance > 1) ||
		(forwardDistance == 0 && rightDistance == 0 && leftDistance == 0))
	{
		return false;
	}
	else
	{
		// Choose which direction to turn (left or right)
		if (rightDistance > leftDistance)
		{
			this->_nextBehaviors.clear();
			this->addNext(new TurnRight(_robot));
		}
		else
		{
			this->_nextBehaviors.clear();
			this->addNext(new TurnLeft(_robot));
		}
		return true;
	}
}

void MoveForward::action() {
	_robot->setSpeed(FORWARD_SPEED, 0);
}

MoveForward::MoveForward(Robot *robot) :
	Movement(robot) {
}

MoveForward::~MoveForward() {
}
