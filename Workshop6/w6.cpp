/*
OOP345 workshop 6 - Lambda Expression
Name           : Eunsol Lee
Date           : November 1st, 2016(Tue)
Student Number : 029-557-154
*/

#include <iostream>
#include "Grades.h"

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << argv[0] <<
			": incorrect number of arguments\n";
		std::cerr << "Usage: " << argv[0] << " file_name\n";
		return 1;
	}

	Grades grades(argv[1]);
	// define the lambda expression for letter
	// take the number(mark) and return string
	auto letter = [](double mark)->string{
		string Grade;
		if (mark >= 90)
			Grade = "A+";
		else if (mark >= 80)
			Grade = "A";
		else if (mark >= 75)
			Grade = "B+";
		else if (mark >= 70)
			Grade = "B";
		else if (mark >= 65)
			Grade = "C+";
		else if (mark >= 60)
			Grade = "C";
		else if (mark >= 55)
			Grade = "D+";
		else if (mark >= 50)
			Grade = "D";
		else
			Grade = "F";
		return Grade;	
	};

	grades.displayGrades(std::cout, letter);

	std::cout << "Press any key to continue ... ";
	std::cin.get();

	return 0;
}