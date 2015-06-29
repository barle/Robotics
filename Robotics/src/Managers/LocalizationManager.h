#ifndef LOCALIZATIONMANAGER_H_
#define LOCALIZATIONMANAGER_H_

#define NUM_OF_PARTICLES 1000
#define PARTICLE_MIN_BELIEF 0.5
#define RANDOMIZE_FACTOR 10
#define PARTICLES_TO_PRINT 3

using namespace std;

#include <vector>
#include"../Models/Particle.h"
#include "../Map.h"
#include "../Robot.h"

class LocalizationManager {
private:
	Map *_map;
	Robot* _robot;
	vector<Particle*> _particles;

	void createAllParticles();
	void filterParticles(double xDeltaInMeter, double yDeltaInMeter, double yawDeltaRadian, float* laserScans);
	void resampleParticles(double xDeltaInMeter, double yDeltaInMeter, double yawDeltaRadian, float* laserScans);

public:
	LocalizationManager(Map *map, Robot* robot);
	void Update(double xDeltaInMeter, double yDeltaInMeter, double yawDeltaRadian, float* laserScans);
	void PrintParticles();
	virtual ~LocalizationManager();
};

#endif /* LOCALIZATIONMANAGER_H_ */
