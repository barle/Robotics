#include "Manager.h"

Manager::Manager(Plan *plan, Robot *robot) {
	this->_robot = robot;
	this->_plan = plan;
}

void Manager::run() {
	//this->_robot->_pp->SetMotorEnable(true); //Todo: enable this when connecting to the real robot
	Behavior *currBeh = this->_plan->getStartBehavior();

	if (!currBeh->startCond()) {
		return;
	}

	int readsCounter = 1;

	while (!currBeh->stopCond()) {
		_robot->read();
		currBeh->action();

		// Every 20 reads make all the calculations and update the particles and their corresponding data
		if (readsCounter == 20)
		{
			double deltaX;
			double deltaY;
			double deltaYaw;
			float *laserScans = this->_robot->getLaserScan();

			//Todo: update all the things we want on the robot: for example localization manager(?)

			readsCounter = 1;
		}
		else
		{
			readsCounter++;
		}

		if (currBeh->stopCond())
			currBeh = currBeh->selectNext();
	}
}

Manager::~Manager() {
}
