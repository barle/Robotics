/*
 * Size.cpp
 *
 *  Created on: Jun 23, 2015
 *      Author: colman
 */

#include "Size.h"

Size::Size(double height, double width) {
	_height = height;
	_width = width;

}

double Size::Height()
{
	return _height;
}

double Size::Width()
{
	return _width;
}

Size::~Size() {
	// TODO Auto-generated destructor stub
}

