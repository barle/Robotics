#ifndef PARTICLE_H_
#define PARTICLE_H_

#define NORMAL_MOVING 10
#define MAX_MOVING 20

#define NORMAL_YAW_DEGREES 180
#define MAX_YAW_DEGREES 360

#define YAW_HIGH_PROB 1
#define YAW_OK_PROB 0.85
#define YAW_LOW_PROB 0.7

#define MOVING_HIGH_PROB 1
#define MOVING_OK_PROB 0.85
#define MOVING_LOW_PROB 0.7

#define MAP_MAX_X 40
#define MAP_MAX_Y 20
#define MAP_RESOLUTION 0.5

#define MAP_MAX_CELLS_LASER 5
#define LASER_MAX_RANGE 4
#define LASER_JUMP_INDEX 1
#define LASER_COUNT 666

#define MAP_FREE 0
#define MAP_OCCUPIED 1
#define MAP_UNKNOWN 2

#define MEASURING_AREA 0.36
#define ANGULAR_RESOLUTION 240

#include "Map.h"
#include <vector>
#include <cmath>
#include <libplayerc++/playerc++.h>

using namespace std;

class Particle {
private:
	int _xVal;
	int _yVal;
	double _yawVal;
	double _belief;
	Map* _map;
	double GetMovingProbability(double xDelta, double yDelta, double yawDelta);
	double UpdateMapAndCheckProbability(double* laserScans);
	double AngleOfIndex(int index);

public:
	Particle(int xPos, int yPos, double yawPos);
	Particle(int xPos, int yPos, double yawPos, Map* map, double belief);
	int GetY();
	int GetX();
	double GetYaw();
	Map* GetMap();
	void Update(double xDelta, double yDelta, double yawDelta, double* laserScans);
	vector<Particle*> CreateNewParticles();
	double GetBelief();
	void Print();
	virtual ~Particle();
};

#endif /* PARTICLE_H_ */
