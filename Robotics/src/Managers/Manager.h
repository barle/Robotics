/*
 * Manager.h
 *
 *  Created on: Jun 20, 2015
 *      Author: colman
 */

#ifndef MANAGER_H_
#define MANAGER_H_

#include "../Robot.h"
#include "../Plans/Plan.h"
#include "../Behaviors/Behavior.h"
#include "LocalizationManager.h"
#include "../Map.h"
#include "../Models/Particle.h"

class Manager{
	private:
		Robot *_robot;
		Plan *_plan;
		LocalizationManager *_loc;
		Map *_map;

	public:
		Manager(Plan *plan, LocalizationManager *loc, Robot *robot, Map *map);
		void run();
		virtual ~Manager();

};

#endif /* MANAGER_H_ */
