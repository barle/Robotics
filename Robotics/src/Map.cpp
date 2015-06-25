/*
 * Map.cpp
 *
 *  Created on: Jun 22, 2015
 *      Author: colman
 */

#include "Map.h"
#include <libplayerc++/playerc++.h>
#include <iostream>
#include <fstream>
#include"lodepng.h"

using namespace std;

vector<bool> loadMap(const char* fileName, unsigned& width, unsigned& height);


Map::Map(const char* filePath) {
	this->_grid = loadMap(filePath, this->_width, this->_height);
/* Todo: remove this.. this is only test printing the map
	for (int i=0;i<this->height;i++)
	{
		for (int j=0; j<this->width; j++)
		{
			cout<< this->grid[(this->width * i) + j];
		}
		cout <<endl;
	}
	*/
}

Map::~Map() {
	// TODO Auto-generated destructor stub
}

vector<bool> Map::GetGrid() {
	return this->_grid;
}

unsigned Map::GetHeight() {
	return this->_height;
}

unsigned Map::GetWidth() {
	return this->_width;
}

double Map::GetResolution()
{
	return this->_resolution;
}

vector<unsigned char> image; //the raw pixels
unsigned pixlesToAdd = 3;

vector<bool> loadMap(const char* fileName, unsigned& width, unsigned& height)
{
	unsigned error = lodepng::decode(image, width, height, (const char*)fileName);

	// If there's an error, display it
	if(error) cout << "decoder error " << error << ": " << lodepng_error_text(error) << endl;

	unsigned size = height * width * 4;
    vector<unsigned char> newImage(size);
    vector<bool> grid(height * width);

    for(unsigned i = 0; i < height ; i++)
    {
        for(unsigned j = 0; j < width * 4; j+=4)
        {
            newImage[(width * 4* i) + j] = (int)image[(width * 4* i) + j];
            newImage[(width * 4* i) + j + 1] = (int)image[(width * 4* i) + j + 1];
            newImage[(width * 4* i) + j + 2] = (int)image[(width * 4* i) + j + 2];

            newImage[(width * 4* i) + j + 3] = 255;
        }
    }

    for(unsigned i = 0; i < height ; i++)
    {
        for(unsigned j = 0; j < width * 4; j+=4)
        {
            // Black
            if((unsigned)image[(width * 4* i) + j] == 0)
            {
                // Color the cell
                newImage[(width * 4* i) + j] = 0;
                newImage[(width * 4* i) + j + 1] = 0;
                newImage[(width * 4* i) + j + 2] = 0;

                // Up cell
                for(unsigned k = 0; k < pixlesToAdd; k++)
                {
                    if((width * 4* (i - k)) + j > 0 &&
                      (width * 4* (i - k)) + j < size)
                    {
                        newImage[(width * 4* (i - k)) + j] = 0;
                        newImage[(width * 4* (i - k)) + j + 1] = 0;
                        newImage[(width * 4* (i - k)) + j + 2] = 0;
                    }
                }

                // Down cell
                for(unsigned k = 0; k < pixlesToAdd; k++)
                {
                    if((width * 4* (i + k)) + j > 0 &&
                      (width * 4* (i + k)) + j < size)
                    {
                        newImage[(width * 4* (i + k)) + j] = 0;
                        newImage[(width * 4* (i + k)) + j + 1] = 0;
                        newImage[(width * 4* (i + k)) + j + 2] = 0;
                    }
                }

                // Right cell
                for(unsigned k = 0; k < pixlesToAdd; k++)
                {
                    if((width * 4* i) + j + k*4 < (width * 4* (i + 1)) &&
                      (width * 4* i) + j + k*4 > (width * 4* (i - 1)))
                    {
                        newImage[(width * 4* i) + j + k*4] = 0;
                        newImage[(width * 4* i) + j + k*4 + 1] = 0;
                        newImage[(width * 4* i) + j + k*4 + 2] = 0;
                    }
                }

                // Left cell
                for(unsigned k = 0; k < pixlesToAdd; k++)
                {
                    if((width * 4* i) + j - k*4 < (width * 4* (i + 1)) &&
                      (width * 4* i) + j - k*4 > (width * 4* (i - 1)))
                    {
                        newImage[(width * 4* i) + j - k*4] = 0;
                        newImage[(width * 4* i) + j - k*4 + 1] = 0;
                        newImage[(width * 4* i) + j - k*4 + 2] = 0;
                    }
                }

            }
        }
    }

    // generate the grid bitmap from the new image
    for(unsigned i = 0; i < height ;i++)
    {
        for(unsigned j = 0; j < width * 4 ;j += 4)
        {
            if (newImage[(width * 4 * i) + j] == 255)
            {
                grid[(width * i) + j/4] = 0; // Free to move
            }
            else
            {
                grid[(width * i) + j/4] = 1; // Wall
            }
        }
    }

    return grid;
}


bool Map::IsOccupied(int x, int y)
{
	return _grid[(_width*y)+x] == 0;
}
