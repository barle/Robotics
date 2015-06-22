#include "Behavior.h"

Behavior *Behavior::selectNext() {
	for (int i = 0; i < _nextBehaviors.size(); i++) {
		if (_nextBehaviors[i]->startCond())
			return _nextBehaviors[i];
	}

	return NULL;
}

Behavior *Behavior::addNext(Behavior *beh) {
	_nextBehaviors.push_back(beh);
	return this;
}


Behavior::Behavior(Robot *robot) {
	_robot = robot;
}

Behavior::~Behavior() {
}
