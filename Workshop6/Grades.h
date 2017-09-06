/*
OOP345 workshop 6
Name           : Eunsol Lee
Date           : November 1st, 2016(Tue)
Student Number : 029-557-154
*/

#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Grades{
	string* stdNo; // Student numbers
	double* mark; // Student marks
	int count;

public:
	// Default Constructor
	Grades() : stdNo(nullptr), mark(nullptr), count(0){}

	// Receives the address of a C-style null-terminated string that contains the name of the file 
	// holding the grade information for all students in a course 
	Grades(char* filename){
		try{
			ifstream is(filename);
			if (!is)
				// If the object cannot open the file, throws an exception with a suitable message
				throw "Cannot open the file";

			if (is.is_open()){
				string line;
				int c = 0;
				while (getline(is, line)){
					c++;
				}
				count = c;

				// Read the file
				is.clear(); // Reset the END-OF-FILE error state
				is.seekg(0, ios_base::beg); // Position file at the beginning
				
				// Allocates memory dynamically and stores information
				stdNo = new string[count];
				mark = new double[count];
				for (int i = 0; i < count; i++){
					is >> stdNo[i];
					is >> mark[i];
				}
				is.close();
			}
		} // try
		catch(ifstream::failure fail){
			cerr << "Cannot open the file";
		}
	} // Grades(char* filename)
	
	// destructor
	~Grades(){
		delete[] stdNo;
		delete[] mark;
	}

	// Receives a reference to the output stream object 
	// and the expression to be used in determining the letter grade 
	// Displays the student number, grade, and the letter
	template<typename F>
	void displayGrades(ostream& os, F f) const{
		for (int i = 0; i < count; i++){
			os << stdNo[i] << " " << mark[i] << "0 " << f(mark[i]) << "\n";
		}
	}

	// Prevent the copying, moving and assigning of an object
	Grades(const Grades&) = delete;
	Grades(Grades&&) = delete;
	Grades& operator=(const Grades&) = delete;
	Grades&& operator=(Grades&&) = delete;
};
