#include "Particle.h"

Particle::Particle(double xPos, double yPos, double yawPos, Map* map, Robot* robot)
{
	this->_belief = 1;
	this->_positionInMeter = new Position(xPos, yPos, yawPos);
	this->_map = map;
	this->_robot = robot;
}

Particle::Particle(double xPos, double yPos, double yawPos, double belief, Map* map, Robot* robot)
{
	this->_belief = belief;
	this->_positionInMeter = new Position(xPos, yPos, yawPos);
	this->_map = map;
	this->_robot = robot;
}

double Particle::GetMovingProbability(double xDeltaInMeter, double yDeltaInMeter, double yawDeltaInRadian)
{
	// Check if we didn't bypass the map's gridlines
	if (this->_positionInMeter->X() > _map->convertPixelToMeter(_map->GetWidth()) ||
			this->_positionInMeter->Y() > _map->convertPixelToMeter(_map->GetHeight()) ||
			this->_positionInMeter->X() < 0 || this->_positionInMeter->Y() < 0)
	{
		return 0;
	}

	double distanceMovedInMeter = sqrt(pow(xDeltaInMeter, 2) + pow(yDeltaInMeter, 2));
	double probYaw = YAW_LOW_PROB;
	double probMoving = MOVING_LOW_PROB;

	// Make sure we didn't rotate to much
	if (yawDeltaInRadian < DTOR(NORMAL_YAW_DEGREES) && yawDeltaInRadian > (-1) * DTOR(NORMAL_YAW_DEGREES))
	{
		probYaw = YAW_HIGH_PROB;
	}
	else if (yawDeltaInRadian < DTOR(MAX_YAW_DEGREES) && yawDeltaInRadian > (-1) * DTOR(MAX_YAW_DEGREES))
	{
		probYaw = YAW_OK_PROB;
	}

	// Make sure we moved by a logical distance
	if (distanceMovedInMeter < _map->convertPixelToMeter(NORMAL_MOVING_PIXELS) && distanceMovedInMeter > (-1) * _map->convertPixelToMeter(NORMAL_MOVING_PIXELS))
	{
		probMoving = MOVING_HIGH_PROB;
	}
	else if (distanceMovedInMeter < _map->convertPixelToMeter(MAX_MOVING_PIXELS) && distanceMovedInMeter > (-1) * _map->convertPixelToMeter(MAX_MOVING_PIXELS))
	{
		probMoving = MOVING_OK_PROB;
	}

	return probYaw * probMoving;
}

double Particle::CheckProbability(float* laserScans)
{
	double hits = 0;
	double misses = 0;

	float xPosInPixel = _map->convertMeterToPixel(this->_positionInMeter->X());
	float yPosInPixel = _map->convertMeterToPixel(this->_positionInMeter->Y());

	// Go over the laser's array
	for (int index = 0; index < LASER_COUNT; index++)
	{
		if (laserScans[index] < LASER_MAX_RANGE)
		{
			// Go over the relevant cells in between the occupied cell and the free cells
			int occupiedCellIndex = (laserScans[index] / LASER_MAX_RANGE) * MAP_MAX_CELLS_LASER;
			for(int j = 0; j < occupiedCellIndex; j++)
			{
				int XFreePosInPixel = xPosInPixel + (cos(DTOR(AngleOfIndex(index)) + this->_positionInMeter->Yaw()) * j);
				int YFreePosInPixel = yPosInPixel + (sin(DTOR(AngleOfIndex(index)) + this->_positionInMeter->Yaw()) * j);

				// Make sure we are in safe bounds
				if (XFreePosInPixel >= 0 && XFreePosInPixel < _map->GetWidth() &&
						YFreePosInPixel >= 0 && YFreePosInPixel < _map->GetHeight())
				{
					if (this->_map->IsOccupiedInOriginalMap(XFreePosInPixel, YFreePosInPixel))
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
			float deltaXInPixels = cos(DTOR(AngleOfIndex(index)) + this->_positionInMeter->Yaw()) *
					((laserScans[index] / LASER_MAX_RANGE) * MAP_MAX_CELLS_LASER);
			float deltaYInPixels = sin(DTOR(AngleOfIndex(index)) + this->_positionInMeter->Yaw()) *
					((laserScans[index] / LASER_MAX_RANGE) * MAP_MAX_CELLS_LASER);

			int XOccupiedPosInPixel = xPosInPixel + deltaXInPixels;
			int YOccupiedPosInPixel = yPosInPixel + deltaYInPixels;


			// Make sure we are in safe array bounds
			if (XOccupiedPosInPixel >= 0 && XOccupiedPosInPixel < _map->GetWidth() &&
					YOccupiedPosInPixel >= 0 && YOccupiedPosInPixel < _map->GetHeight())
			{
				if (this->_map->IsOccupiedInOriginalMap(XOccupiedPosInPixel, YOccupiedPosInPixel))
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
			for(int j = 0; j < _map->convertPixelToMeter((laserScans[index] / LASER_MAX_RANGE) * MAP_MAX_CELLS_LASER); j++)
			{
				int XFreePosInPixel = xPosInPixel + (cos(DTOR(AngleOfIndex(index)) + this->_positionInMeter->Yaw()) * j);
				int YFreePosInPixel = yPosInPixel + (sin(DTOR(AngleOfIndex(index)) + this->_positionInMeter->Yaw()) * j);


				// Make sure we are in safe array bounds
				if (XFreePosInPixel >= 0 && XFreePosInPixel < _map->GetWidth() &&
						YFreePosInPixel >= 0 && YFreePosInPixel < _map->GetHeight())
				{
					if (this->_map->IsOccupiedInOriginalMap(XFreePosInPixel, YFreePosInPixel))
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
	if (misses != 0 || hits != 0)
	{
		return hits / (hits + misses);
	}
	return 1;
}

double Particle::AngleOfIndex(int index)
{
	// Calculate angle by laser index
	return index * (MEASURING_AREA / LASER_COUNT);
}

void Particle::Update(double xDelta, double yDelta, double yawDelta, float* laserScans)
{
	double x = this->_positionInMeter->X();
	double y = this->_positionInMeter->Y();
	double yaw = this-> _positionInMeter->Yaw();
	this->_positionInMeter->Update(x + xDelta, y + yDelta, yaw + yawDelta);

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
	return this->_positionInMeter;
}

double Particle::GetBelief()
{
	return this->_belief;
}

void Particle::Print()
{
	// Print robot position
	_robot->drawPoint(this->_map->convertMeterToPixel(_positionInMeter->X()), _map->convertMeterToPixel(_positionInMeter->Y()), 0.5, 0, 0, 0);
}

Particle::~Particle() {

}
