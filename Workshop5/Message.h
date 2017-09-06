/*
OOP345 workshop 5
Name           : Eunsol Lee
Date           : October 24, 2016(Mon)
Student Number : 029-557-154
*/

#pragma once
#include <iostream>
#include <fstream>
#include <string>

namespace w5{
	class Message{
		std::string user, tweet, reply;

	public:
		Message(){}
		Message(std::ifstream& in, char c);		
		bool empty() const;		
		void display(std::ostream& os) const;
	};
}