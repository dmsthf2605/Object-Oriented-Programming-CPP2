/*
OOP345 workshop 7 - STL Containers
Name           : Eunsol Lee
Date           : November 6th, 2016(Sun)
Student Number : 029-557-154
*/

// the main program receives the name of the file that holds information about the products sold to a customer
#include <iostream>
#include <string>
#include "Sale.h"

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cerr << argv[0] << ": incorrect number of arguments\n";
		std::cerr << "Usage: " << argv[0] << " file_name\n";
		return 1;
	}

	w7::Sale sale(argv[1]);
	sale.display(std::cout);

	std::cout << "\nPress any key to continue ... ";
	std::cin.get();
}