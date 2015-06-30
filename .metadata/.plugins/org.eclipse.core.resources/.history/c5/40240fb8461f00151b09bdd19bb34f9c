#include "TurnLeft.h"
#include "MoveForward.h"

bool TurnLeft::startCond()
{
	// Create the behavior with default next behavior to move forward
	this->_nextBehaviors.clear();
	this->addNext(new MoveForward(_robot));
	return true;
}

bool TurnLeft::stopCond()
{
	double forwardDistance = Get0DegreeDistance();
	double rightDistance = Get45DegreeDistance();
	double leftDistance = Get315DegreeDistance();

	// make sure we can move left
	if ((forwardDistance > 1 && rightDistance > 1 && leftDistance > 1) ||
		(forwardDistance == 0 && rightDistance == 0 && leftDistance == 0))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void TurnLeft::action()
{
	_robot->setSpeed(TURN_SPEED, -0.5);
}

TurnLeft::TurnLeft(Robot *robot) : Movement(robot) {
}

TurnLeft::~TurnLeft() {
}
