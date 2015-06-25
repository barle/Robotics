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

class LocalizationManager {
private:
	Map *_map;
	vector<Particle*> _particles;

public:
	LocalizationManager(Map *map);
	void Update(double xDelta, double yDelta, double yawDelta, float* laserScans);
	void PrintParticles();
	virtual ~LocalizationManager();
};

#endif /* LOCALIZATIONMANAGER_H_ */
