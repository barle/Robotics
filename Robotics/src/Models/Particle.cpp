#include "Particle.h"

Particle::Particle(int xPos, int yPos, double yawPos)
{
	this->_belief = 1;
	this->_xVal = xPos;
	this->_yVal = yPos;
	this->_yawVal = yawPos;
	this->_map = new Map();
}

Particle::Particle(int xPos, int yPos, double yawPos, Map* map, double belief)
{
	this->_belief = belief;
	this->_xVal = xPos;
	this->_yVal = yPos;
	this->_yawVal = yawPos;
	this->_map = new Map(map);
}

double Particle::GetMovingProbability(double xDelta, double yDelta, double yawDelta)
{
	// Check if we didn't bypass the map's gridlines
	if (xDelta + this->_xVal > MAP_MAX_X / RESOLUTION || yDelta + this->_yVal > MAP_MAX_Y / RESOLUTION)
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
}

double Particle::UpdateMapAndCheckProbability(double* laserScans)
{
	double hits = 0;
	double misses = 0;

	// Go over the laser's array by a constant jump range
	for (int index = 0; index < LASER_COUNT; index += LASER_JUMP_INDEX)
	{
		if (laserScans[index] < LASER_MAX_RANGE)
		{
			// Go over the relevant cells in between the occupied cell and the free cells
			for(int j = 0; j < (((laserScans[index] / LASER_MAX_RANGE) * MAP_MAX_CELLS_LASER) / RESOLUTION); j++)
			{
				int XFreePos = this->_xVal + (sin(DTOR(AngleOfIndex(index)) + this->_yawVal) * j);
				int YFreePos = this->_yVal + (cos(DTOR(AngleOfIndex(index)) + this->_yawVal) * j);

				// Make sure we are in safe bounds
				if (XFreePos >= 0 && XFreePos < MAP_MAX_X / RESOLUTION && YFreePos >= 0 && YFreePos < MAP_MAX_Y / RESOLUTION)
				{
					if (this->_map->GetOccupancyStatus(YFreePos, XFreePos) == MAP_FREE)
					{
						hits++;
					}
					else if (this->_map->GetOccupancyStatus(YFreePos, XFreePos) == MAP_OCCUPIED)
					{
						misses++;
					}

					// Update the cell by it's new value
					this->_map->UpdateCell(YFreePos, XFreePos, MAP_FREE);
				}
			}

			// Calculate the occupied position
			int XOccupiedPos = this->_xVal + (sin(DTOR(AngleOfIndex(index)) + this->_yawVal) * (((laserScans[index] / LASER_MAX_RANGE) * MAP_MAX_CELLS_LASER) / RESOLUTION));
			int YOccupiedPos = this->_yVal + (cos(DTOR(AngleOfIndex(index)) + this->_yawVal) * (((laserScans[index] / LASER_MAX_RANGE) * MAP_MAX_CELLS_LASER) / RESOLUTION));

			// Make sure we are in safe array bounds
			if (XOccupiedPos >= 0 && XOccupiedPos < MAP_MAX_X / RESOLUTION && YOccupiedPos >= 0 && YOccupiedPos < MAP_MAX_Y / RESOLUTION)
			{
				if (this->_map->GetOccupancyStatus(YOccupiedPos, XOccupiedPos) == MAP_OCCUPIED)
				{
					hits++;
				}
				else if (this->_map->GetOccupancyStatus(YOccupiedPos, XOccupiedPos) == MAP_FREE)
				{
					misses++;
				}

				// Update the cell
				this->_map->UpdateCell(YOccupiedPos, XOccupiedPos, MAP_OCCUPIED);
			}
		}
		else
		{
			// Go over all the cells in this angle and make sure we mark them as free
			for(int j = 0; j < (((laserScans[index] / LASER_MAX_RANGE) * MAP_MAX_CELLS_LASER) / RESOLUTION); j += 1)
			{
				int XFreePos = this->_xVal + (sin(DTOR(AngleOfIndex(index)) + this->_yawVal) * j);
				int YFreePos = this->_yVal + (cos(DTOR(AngleOfIndex(index)) + this->_yawVal) * j);

				// Make sure we are in safe array bounds
				if (XFreePos >= 0 && XFreePos < MAP_MAX_X / RESOLUTION && YFreePos >= 0 && YFreePos < MAP_MAX_Y / RESOLUTION)
				{
					if (this->_map->GetOccupancyStatus(YFreePos, XFreePos) == MAP_FREE)
					{
						hits++;
					}
					else if (this->_map->GetOccupancyStatus(YFreePos, XFreePos) == MAP_OCCUPIED)
					{
						misses++;
					}

					this->_map->UpdateCell(YFreePos, XFreePos, MAP_FREE);
				}
			}
		}
	}

	// Calculate hits/total value
	if (hits != 0 || misses != 0)
	{
		return hits / (hits + misses);
	}
	else
	{
		return 1;
	}
}

double Particle::AngleOfIndex(int index)
{
	// Calculate angle by laser index
	return index * MEASURING_AREA - 360 + ANGULAR_RESOLUTION;
}

void Particle::Update(double xDelta, double yDelta, double yawDelta, double* laserScans)
{
	this->_xVal += xDelta / RESOLUTION;
	this->_yVal += yDelta / RESOLUTION;
	this->_yawVal += yawDelta;

	// Calculate belief by moving probability
	this->_belief = this->_belief * Particle::GetMovingProbability(xDelta, yDelta, yawDelta);

	if (this->_belief != 0)
	{
		// Calculate belief by map relevance probability
		this->_belief = this->_belief * Particle::UpdateMapAndCheckProbability(laserScans);
	}
}

int Particle::GetX()
{
	return this->_xVal;
}

int Particle::GetY()
{
	return this->_yVal;
}

double Particle::GetYaw()
{
	return this->_yawVal;
}

Map* Particle::GetMap()
{
	return this->_map;
}

double Particle::GetBelief()
{
	return this->_belief;
}

void Particle::Print()
{
	// Print robot position and map
	cout << "Robot position: " << this->_xVal << ", " << this->_yVal << ", yaw: " << this->_yawVal << endl;
	cout << "Map: " << endl;
	this->_map->PrintMap();
}

Particle::~Particle() {

}