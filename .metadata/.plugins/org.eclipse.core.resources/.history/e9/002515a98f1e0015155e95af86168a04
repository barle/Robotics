#include "Manager.h"

Manager::Manager(Plan *plan, LocalizationManager *loc, Robot *robot) {
	this->_robot = robot;
	this->_plan = plan;
	this->_loc = loc;
}

void Manager::run() {
	//this->_robot->_pp->SetMotorEnable(true); //Todo: enable this when connecting to the real robot
	Behavior *currBeh = this->_plan->getStartBehavior();
	if(currBeh->stopCond())
			currBeh = currBeh->selectNext();

	int readsCounter = 1;
	while (currBeh && !currBeh->stopCond()) {
		_robot->drawPoint(_robot->getX(),_robot->getY(), 2, 0, 255, 0);

		_robot->read();
		currBeh->action();

		// Every 20 reads make all the calculations and update the particles and their corresponding data
		if (readsCounter == 20)
		{
			//draw current location:
			double deltaX;
			double deltaY;
			double deltaYaw;
			float *laserScans = this->_robot->getLaserScan();

			// Set robot delta values
			this->_robot->SetDeltaValues(deltaX, deltaY, deltaYaw);

			_loc->Update(deltaX,deltaY, deltaYaw, laserScans);
			//_loc->PrintParticles();

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
