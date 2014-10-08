//============================================================================
// Name        : HW2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "DLList.h"

using namespace ods;
using namespace std;

int main() {

	DLList<char> myDLList1;
	myDLList1.add('r');
	myDLList1.add('a');
	myDLList1.add('c');
	myDLList1.add('e');
	DLList<char> myDLList2;
	myDLList2.add('c');
	myDLList2.add('a');
	myDLList2.add('r');
	DLList<char> myEmptyList;

	//***JUST UNCOMMENT EACH PART TO TEST***

	/*
	// test for part 1
	cout << boolalpha << myDLList1.isPalindrome() << endl;
	cout << "--------------------------------" << endl;
	*/

	/*
	// test for part 2
	myDLList1.rotate(0);
	for (int i = 0; i < myDLList1.size(); i++) {
		cout << myDLList1.get(i) << endl;
	}
	cout << "--------------------------------" << endl;
	 */

	/*
	// test for part 3
	myDLList1.absorb(myDLList2);
	for (int i = 0; i < myDLList1.size(); i++) {
		cout << myDLList1.get(i) << endl;
	}
	cout << "--------------------------------" << endl;
	for (int i = 0; i < myDLList2.size(); i++) {
		cout << myDLList2.get(i) << endl;
	}
	cout << "--------------------------------" << endl;
	*/

	/*
	// test for part 4
	myDLList1.deal(myEmptyList);
	for (int i = 0; i < myEmptyList.size(); i++) {
		cout << myEmptyList.get(i) << endl;
	}
	cout << "--------------------------------" << endl;
	*/
	return 0;
}
