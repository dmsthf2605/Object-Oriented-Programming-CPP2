/*
OOP345 workshop 5
Name           : Eunsol Lee
Date           : October 24, 2016(Mon)
Student Number : 029-557-154
*/

#include "Notifications.h"
#include <iostream>

using namespace std;

namespace w5{
	// default constructor - empty
	Notifications::Notifications() : count(0), MessageTable(new Message[CAPACITY]){ }

	// copy constructor
	Notifications::Notifications(const Notifications& rhs) : count(0), MessageTable(nullptr){
		*this = rhs;
	}

	// copy assignment operator
	Notifications& Notifications::operator=(const Notifications& rhs){ 
		if (this != &rhs){
			delete[] MessageTable;
			MessageTable = nullptr;

			count = rhs.count;
			MessageTable = new Message[CAPACITY];
			for (size_t i = 0; i < count; i++){ // deep copying
				MessageTable[i] = rhs.MessageTable[i];
			}
		}
		return *this;
	}	

	// move constructor
	Notifications::Notifications(Notifications&& rhs) : count(rhs.count), MessageTable(rhs.MessageTable) { 
		rhs.count = 0;
		rhs.MessageTable = nullptr;
	}

	// move assignment operator
	Notifications&& Notifications::operator=(Notifications&& rhs){ 
		if (this != &rhs){
			delete[] MessageTable;
			MessageTable = nullptr;

			count = rhs.count;
			MessageTable = rhs.MessageTable;

			rhs.count = 0;
			rhs.MessageTable = nullptr;
		}
		return move(*this);
	}

	// destructor
	Notifications::~Notifications(){ delete[] MessageTable; }

	// adds msg to the set
	void Notifications::operator+=(const Message& msg){ 
		if ((int)count < CAPACITY){
			MessageTable[count] = msg;
			count++;
		}
	}

	// inserts the Message objects to the os output stream
	void Notifications::display(std::ostream& os) const{ 
		for (size_t i = 0; i < count; i++){
			MessageTable[i].display(os);
		}
	}
}