/*
 * Position.h
 *
 *  Created on: Jun 23, 2015
 *      Author: colman
 */

#ifndef POSITION_H_
#define POSITION_H_

class Position {
private:
	double _yaw;
	double _x;
	double _y;
public:
	double Yaw();
	double X();
	double Y();
	Position(double x, double y, double yaw = 0);
	virtual ~Position();
};

#endif /* POSITION_H_ */
