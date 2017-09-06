/*
OOP345 workshop 5
Name           : Eunsol Lee
Date           : October 24, 2016(Mon)
Student Number : 029-557-154
*/

#pragma once
#include "Message.h"

namespace w5{
	const int CAPACITY = 10;
	class Notifications{
		size_t count;
		Message* MessageTable;

	public:
		Notifications();		
		Notifications(const Notifications&);
		Notifications& operator=(const Notifications&);
		Notifications(Notifications&&);
		Notifications&& operator=(Notifications&&);
		~Notifications();
		void operator+=(const Message& msg);
		void display(std::ostream& os) const;
	};
}