#ifndef SLAMMANAGER_H_
#define SLAMMANAGER_H_

#define NUM_OF_PARTICLES 20
#define MAX_X_POS 40
#define MAX_Y_POS 20
#define RESOLUTION 0.2
#define PARTICLE_MIN_BELIEF 0.5
#define RANDOMIZE_FACTOR 10
#define PARTICLES_TO_PRINT 3
#define MAX_DEGREES 360

#include<vector.h>
#include"Particle.h"

using namespace std;

class SlamManager {
private:
	vector<Particle*> _particles;

public:
	SlamManager();
	void Update(double xDelta, double yDelta, double yawDelta, double* laserScans);
	void PrintParticles();
	virtual ~SlamManager();
};

#endif /* SLAMMANAGER_H_ */
