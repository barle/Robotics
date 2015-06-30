#ifndef LOCALIZATIONMANAGER_H_
#define LOCALIZATIONMANAGER_H_

#define NUM_OF_PARTICLES 100
#define MAX_NUM_OF_PARTICLES 200
#define NUM_OF_DUPLICATIONS 5
#define PARTICLE_MIN_BELIEF 0.7
#define RANDOMIZE_FACTOR 2

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
	void filterParticles();
	void resampleParticles();

public:
	LocalizationManager(Map *map, Robot* robot);
	void Update(double xDeltaInPixel, double yDeltaInPixel, double yawDeltaDegree, float* laserScans);
	Position *GetBestPosition();
	void PrintParticles();
	virtual ~LocalizationManager();
};

#endif /* LOCALIZATIONMANAGER_H_ */
