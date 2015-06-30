#include "ObstacleAvoidPln.h"
#include "../Behaviors/MoveForward.h"
#include "../Behaviors/TurnRight.h"
#include "../Behaviors/TurnLeft.h"

ObstacleAvoidPln::ObstacleAvoidPln(Robot *robot) : Plan(robot) {

	// Create the behaviors with the move forward coming first
	_behaviors.push_back(new MoveForward(robot));
	_behaviors.push_back(new TurnRight(robot));
	_behaviors.push_back(new TurnLeft(robot));

	_behaviors[1]->addNext(_behaviors[0]);
	_behaviors[2]->addNext(_behaviors[0]);
}

Behavior *ObstacleAvoidPln::getStartBehavior() {
	return _behaviors[0];
}

ObstacleAvoidPln::~ObstacleAvoidPln() {
}
