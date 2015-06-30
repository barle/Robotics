#include "Manager.h"

Manager::Manager(Plan *plan, LocalizationManager *loc, Robot *robot, Map *map) {
	this->_robot = robot;
	this->_plan = plan;
	this->_loc = loc;
	this->_map = map;
}

void Manager::run() {
	Behavior *currBeh = this->_plan->getStartBehavior();
	if(currBeh->stopCond())
			currBeh = currBeh->selectNext();

	int readsCounter = 1;
	while (currBeh && !currBeh->stopCond()) {
		//draw current location:
		//_robot->drawPoint(_robot->getX(),_robot->getY(), 2, 0, 255, 0);

		_robot->read();
		currBeh->action();

		// Every 20 reads make all the calculations and update the particles and their corresponding data
		if (readsCounter == 20)
		{
			double deltaXInPixel;
			double deltaYInPixel;
			double deltaYawInDegree;
			float *laserScans = this->_robot->getLaserScan();

			// Set robot delta values
			this->_robot->SetDeltaValues(deltaXInPixel, deltaYInPixel, deltaYawInDegree);

			_loc->Update(deltaXInPixel,deltaYInPixel, deltaYawInDegree, laserScans);

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
