/*
 * rectangle.cpp
 *
 *  Created on: Aug 28, 2014
 *      Author: johns390
 */

#include "rectangle.h"

void Rectangle::set_values (int x, int y) {
	width = x;
	height = y;
}

int Rectangle::area() {
	return width * height;
}


