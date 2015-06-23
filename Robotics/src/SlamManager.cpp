#include "SlamManager.h"

SlamManager::SlamManager() {
	// Build particles
	for (int particleIndex = 0; particleIndex < NUM_OF_PARTICLES; particleIndex++)
	{
		// Make them with random values from within maps bounds
		int xPos = rand() % static_cast<int>(MAX_X_POS / RESOLUTION);
		int yPos = rand() % static_cast<int>(MAX_Y_POS / RESOLUTION);

		double yaw = DTOR(rand() % MAX_DEGREES);

		Particle* particle = new Particle(xPos, yPos, yaw);
		this->_particles.push_back(particle);

		cout << "Added particle" << particleIndex + 1 << ": " << xPos << ", " << yPos << ", yaw: " << yaw << endl;
	}
}

void SlamManager::Update(double xDelta, double yDelta, double yawDelta, double* laserScans)
{
	vector<int> particlesIndexesToErase;
	vector<int> particlesIndexesToDuplicate;
	int numOfParticlesToErase = 0;
	int numOfParticlesToDuplicate = 0;

	// Go over all particles
	for (int particleIndex = 0; particleIndex < NUM_OF_PARTICLES; particleIndex++)
	{
		this->_particles[particleIndex]->Update(xDelta, yDelta, yawDelta, laserScans);

		// Check if we need to erase the current particle or we can duplicate it later
		if (this->_particles[particleIndex]->GetBelief() < PARTICLE_MIN_BELIEF)
		{
			numOfParticlesToErase++;
			particlesIndexesToErase.push_back(particleIndex);
		}
		else
		{
			numOfParticlesToDuplicate++;
			particlesIndexesToDuplicate.push_back(particleIndex);
		}
	}

	// Erase all less accurate particles
	for (int particleEraseIndex = numOfParticlesToErase; particleEraseIndex > 0; particleEraseIndex--)
	{
		this->_particles.erase(this->_particles.begin() + particleEraseIndex);
	}
	for(int j = 0; j < numOfParticlesToErase; j++){
		_particles.erase(_particles.begin());
	}

	bool finishedDuplicating = !(this->_particles.size() < NUM_OF_PARTICLES);

	// Start creating similar particles
	while (!finishedDuplicating)
	{
		for (int duplicateIndex = 0; duplicateIndex < numOfParticlesToDuplicate && !finishedDuplicating; duplicateIndex++)
		{
			double newParticleY = this->_particles[duplicateIndex]->GetY() + static_cast<double>((rand() % (MAX_Y_POS / RANDOMIZE_FACTOR)) - (rand() % (MAX_Y_POS / RANDOMIZE_FACTOR)));
			double newParticleX = this->_particles[duplicateIndex]->GetX() + static_cast<double>((rand() % (MAX_X_POS / RANDOMIZE_FACTOR)) - (rand() % (MAX_X_POS / RANDOMIZE_FACTOR)));
			double newParticleYaw = this->_particles[duplicateIndex]->GetYaw() + (double(rand() % 10) / 100.0) - (double(rand() % 10) / 100.0);

			// Make sure we are in safe bounds
			if (!(newParticleX > MAX_X_POS / RESOLUTION || newParticleY > MAX_Y_POS / RESOLUTION || newParticleY < 0 || newParticleX < 0))
			{
				Particle* newParticle = new Particle(newParticleX, newParticleY, newParticleYaw,
						this->_particles[duplicateIndex]->GetMap(), this->_particles[duplicateIndex]->GetBelief());
				this->_particles.push_back(newParticle);

				finishedDuplicating = !(this->_particles.size() < NUM_OF_PARTICLES);
				cout << "Created new particle: " << newParticleX << ", " << newParticleY << ", yaw: " << newParticleYaw << endl;
			}
		}
	}

}

void SlamManager::PrintParticles()
{
	double belief = 0;
	int index = 0;

	for(vector<int>::size_type i = 0; i != _particles.size(); i++) {
		if(belief < _particles[i]->GetBelief()){
			belief = _particles[i]->GetBelief();
			index = i;
		}
	}
	this->_particles[index]->Print();
}

SlamManager::~SlamManager() {
}
