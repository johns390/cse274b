// classes example
#include <iostream>
#include "rectangle.h"

using namespace std;

void main () {
	Rectangle rect;

	//Creating a reference to the object rect using the & reference operator
	Rectangle &refRect = rect;

	//Creating a copy of the object rect
	Rectangle rect2 = rect;

	//Creating a pointer that points to object rect using the new keyword
	Rectangle *pRect = new Rectangle;

	//If using a pointer, must use the -> operator for accessing the particular function
	pRect->set_values(7,8);

	rect.set_values (3,4);
	rect2.set_values (5,6);
	refRect.set_values (10,5);

	cout << "area: " << rect.area() << endl;
	cout << "area2: " << rect2.area() << endl;
	cout << "arearef: " << refRect.area() << endl;
	cout << "pointer to rect " << pRect << endl;
	cout << "area for pointer " << pRect->area() << endl;
}
