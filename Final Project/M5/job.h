/*
OOP345 Milestone 5
Name           : Eunsol Lee
Date           : December 8th(Thursday)
Student Number : 029-557-154
*/

#pragma once
#include "o.h"

class Job : public Order{
	vector<bool> installed;
public:
	Job(){}
	Job(Order* o) : Order(*o){
		//  The size of ‘installed’ is the number of items in the order
		installed.resize( size() ); // allocate space

		// Initialize the vector to all ‘false’ (item not installed).
		for (size_t i = 0; i < size(); i++)
			installed[i] = false;			
	}

	bool Installed(size_t i) { return installed[i]; }
	void Installed(size_t i, bool value) { installed[i] = value; }
};