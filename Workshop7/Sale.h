/*
OOP345 workshop 7 - STL Containers
Name           : Eunsol Lee
Date           : November 6th, 2016(Sun)
Student Number : 029-557-154
*/

#pragma once
#include <iostream>
#include <vector>
#include "iProduct.h"

namespace w7{
	class Sale{
		// class stores and accesses through a set of pointers to the objects.
		std::vector<iProduct*> pList;
	public:
		Sale(char*);
		void display(std::ostream& os) const;
	};
}