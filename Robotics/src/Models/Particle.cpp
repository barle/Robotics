#include "Particle.h"

Particle::Particle(int xPos, int yPos, double yawPos, Map* map)
{
	this->_belief = 0;
	this->_position = new Position(xPos, yPos, yawPos);
	this->_map = map;
}

Particle::Particle(int xPos, int yPos, double yawPos, double belief, Map* map)
{
	this->_belief = belief;
	this->_position = new Position(xPos, yPos, yawPos);
	this->_map = map;
}

double Particle::GetMovingProbability(double xDelta, double yDelta, double yawDelta)
{
	// Check if we didn't bypass the map's gridlines
	if (xDelta + this->_position->X() > _map->GetWidth() / _map->GetResolution() || yDelta + this->_position->Y() > _map->GetHeight() / _map->GetResolution())
	{
		return 0;
	}
	else
	{
		double distanceMoved = sqrt(pow(xDelta, 2) + pow(yDelta, 2));
		double probYaw = YAW_LOW_PROB;
		double probMoving = MOVING_LOW_PROB;

		// Make sure we didn't rotate to much
		if (yawDelta < DTOR(NORMAL_YAW_DEGREES) && yawDelta > (-1) * DTOR(NORMAL_YAW_DEGREES))
		{
			probYaw = YAW_HIGH_PROB;
		}
		else if (yawDelta < DTOR(MAX_YAW_DEGREES) && yawDelta > (-1) * DTOR(MAX_YAW_DEGREES))
		{
			probYaw = YAW_OK_PROB;
		}

		// Make sure we moved by a logical distance
		if (distanceMoved < NORMAL_MOVING && distanceMoved > (-1) * NORMAL_MOVING)
		{
			probMoving = MOVING_HIGH_PROB;
		}
		else if (distanceMoved < MAX_MOVING && distanceMoved > (-1) * MAX_MOVING)
		{
			probMoving = MOVING_OK_PROB;
		}

		return probYaw * probMoving;
	}
	return 0;
}

double Particle::CheckProbability(float* laserScans)
{
	double hits = 0;
	double misses = 0;

	// Go over the laser's array
	for (int index = 0; index < LASER_COUNT; index++)
	{
		if (laserScans[index] < LASER_MAX_RANGE)
		{
			// Go over the relevant cells in between the occupied cell and the free cells
			for(int j = 0; j < (((laserScans[index] / LASER_MAX_RANGE) * MAP_MAX_CELLS_LASER) / _map->GetResolution()); j++)
			{
				int XFreePos = this->_position->X() + (cos(DTOR(AngleOfIndex(index)) + this->_position->Yaw()) * j);
				int YFreePos = this->_position->Y() + (sin(DTOR(AngleOfIndex(index)) + this->_position->Yaw()) * j);

				// Make sure we are in safe bounds
				if (XFreePos >= 0 && XFreePos < _map->GetWidth() / _map->GetResolution() && YFreePos >= 0 && YFreePos < _map->GetHeight() / _map->GetResolution())
				{
					if (this->_map->IsOccupied(YFreePos, XFreePos))
					{
						misses++;
					}
					else
					{
						hits++;
					}
				}
			}

			// Calculate the occupied position
			int XOccupiedPos = this->_position->X() + (cos(DTOR(AngleOfIndex(index)) + this->_position->Yaw()) * (((laserScans[index] / LASER_MAX_RANGE) * MAP_MAX_CELLS_LASER) / _map->GetResolution()));
			int YOccupiedPos = this->_position->Y() + (sin(DTOR(AngleOfIndex(index)) + this->_position->Yaw()) * (((laserScans[index] / LASER_MAX_RANGE) * MAP_MAX_CELLS_LASER) / _map->GetResolution()));

			// Make sure we are in safe array bounds
			if (XOccupiedPos >= 0 && XOccupiedPos < _map->GetWidth() / _map->GetResolution() && YOccupiedPos >= 0 && YOccupiedPos < _map->GetHeight() / _map->GetResolution())
			{
				if (this->_map->IsOccupied(YOccupiedPos, XOccupiedPos))
				{
					misses++;
				}
				else
				{
					hits++;
				}
			}
		}
		else
		{
			// Go over all the cells in this angle and make sure we mark them as free
			for(int j = 0; j < (((laserScans[index] / LASER_MAX_RANGE) * MAP_MAX_CELLS_LASER) / _map->GetResolution()); j++)
			{
				int XFreePos = this->_position->X() + (cos(DTOR(AngleOfIndex(index)) + this->_position->Yaw()) * j);
				int YFreePos = this->_position->Y() + (sin(DTOR(AngleOfIndex(index)) + this->_position->Yaw()) * j);

				// Make sure we are in safe array bounds
				if (XFreePos >= 0 && XFreePos < _map->GetWidth() / _map->GetResolution() && YFreePos >= 0 && YFreePos < _map->GetHeight() / _map->GetResolution())
				{
					if (this->_map->IsOccupied(YFreePos, XFreePos))
					{
						misses++;
					}
					else
					{
						hits++;
					}
				}
			}
		}

	}

	// Calculate hits/total value
	if (hits != 0 || misses != 0)
	{
		return hits / (hits + misses);
	}
	return 1;
}

double Particle::AngleOfIndex(int index)
{
	// Calculate angle by laser index
	return index * MEASURING_AREA - 360 + ANGULAR_RESOLUTION;
}

void Particle::Update(double xDelta, double yDelta, double yawDelta, float* laserScans)
{
	double x = this->_position->X();
	double y = this->_position->Y();
	double yaw = this-> _position->Yaw();
	this->_position->Update(x + (xDelta / _map->GetResolution()), y + (yDelta / _map->GetResolution()), yaw + yawDelta);

	// Calculate belief by moving probability
	this->_belief = this->_belief * GetMovingProbability(xDelta, yDelta, yawDelta);

	if (this->_belief != 0)
	{
		// Calculate belief by map relevance probability
		this->_belief = this->_belief * CheckProbability(laserScans);
	}

}

Position* Particle::GetPosition()
{
	return this->_position;
}

double Particle::GetBelief()
{
	return this->_belief;
}

void Particle::Print()
{
	// Print robot position
	cout << "Robot position: " << this->_position->X() << ", " << this->_position->Y() << ", yaw: " << this->_position->Yaw() << endl;
}

Particle::~Particle() {

}
