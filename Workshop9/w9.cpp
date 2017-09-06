/*
OOP345 Workshop 9 - Smart Pointers
Name           : Eunsol Lee
Date           : November 16, 2016(Sun)
Student Number : 029-557-154
*/

#include <iostream>
#include <iomanip>
#include <memory>
#include "Element.h"
#include "List.h"

using namespace std;

const int FWC = 5;
const int FWD = 12;
const int FWP = 8;

// compares elements in the two received lists for common product codes 
// and builds the user-friendly list from the matching pairs
w9::List<w9::Product> merge(const w9::List<w9::Description>& desc,
	const w9::List<w9::Price>& price) {
	w9::List<w9::Product> priceList;

	// allocates dynamic memory for each user-friendly element
	// adds element to the new list by passing the object's raw pointer to the list's += operator
	for (unsigned int i = 0; i < desc.size(); i++) {
		for (unsigned int j = 0; j < price.size(); j++) {
			if (desc[i].code == price[j].code) {
				// w9::Product* p = new w9::Product(desc[i].desc, price[j].price);
				unique_ptr<w9::Product> p(new w9::Product(desc[i].desc, price[j].price));
				p->validate();
				priceList += p;
			}
		}
	}
	return priceList;
}

int main(int argc, char** argv) {
	std::cout << "\nCommand Line : ";
	for (int i = 0; i < argc; i++) {
		std::cout << argv[i] << ' ';
	}
	std::cout << std::endl;
	if (argc != 3) {
		std::cerr << "\n***Incorrect number of arguments***\n";
		return 1;
	}

	try {
		w9::List<w9::Description> desc(argv[1]);
		std::cout << std::endl;
		std::cout << std::setw(FWC) << "Code" <<
			std::setw(FWD) << "Description" << std::endl;
		std::cout << desc << std::endl;
		w9::List<w9::Price> price(argv[2]);
		std::cout << std::endl;
		std::cout << std::setw(FWC) << "Code" <<
			std::setw(FWP) << "Price" << std::endl;
		std::cout << price << std::endl;
		w9::List<w9::Product> priceList = merge(desc, price);
		std::cout << std::endl;
		std::cout << std::setw(FWD) << "Description" <<
			std::setw(FWP) << "Price" << std::endl;
		std::cout << priceList << std::endl;
	}
	catch (const std::string& msg) {
		std::cerr << msg << std::endl;
	}
	catch (const char* msg) {
		std::cerr << msg << std::endl;
	}

	std::cout << "\nPress any key to continue ... ";
	std::cin.get();
}
