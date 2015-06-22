#include "Movement.h"



bool Movement::startCond() {
	return true;
}

bool Movement::stopCond() {
	return false;
}

void Movement::action() {
}

double Movement::Get0DegreeDistance()
{
	return GetDistanceByDegree(0);
}

double Movement::Get315DegreeDistance()
{
	return GetDistanceByDegree(-45);
}

double Movement::Get45DegreeDistance()
{
	return GetDistanceByDegree(45);
}

double Movement::GetDistanceByDegree(int degree)
{
	float* scan = _robot->getLaserScan();
	// Calculate laser index by degree
	int scanIndex = _robot->deg_to_index(degree);
	return scan[scanIndex];
}

Movement::Movement(Robot *robot) :	Behavior(robot) {
}

Movement::~Movement() {
}
