/*
 * Size.h
 *
 *  Created on: Jun 23, 2015
 *      Author: colman
 */

#ifndef SIZE_H_
#define SIZE_H_

class Size {
private:
	double _height;
	double _width;
public:
	double Height();
	double Width();
	Size(double height, double width);
	virtual ~Size();
};

#endif /* SIZE_H_ */
