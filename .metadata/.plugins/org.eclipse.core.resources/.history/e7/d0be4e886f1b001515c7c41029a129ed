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

class Manager{
	private:
		Robot *_robot;
		Plan *_plan;

	public:
		Manager(Plan *plan, Robot *robot);
		void run();
		virtual ~Manager();

};

#endif /* MANAGER_H_ */
