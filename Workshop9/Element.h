/*
OOP345 Workshop 9 - Smart Pointers
Name           : Eunsol Lee
Date           : November 16, 2016(Sun)
Student Number : 029-557-154
*/

#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

extern const int FWC;
extern const int FWD;
extern const int FWP;

namespace w9 {

	// holds a product code and a user-friendly description
	struct Description {
		unsigned code;
		std::string desc;

		bool load(std::ifstream& f) {
			f >> code >> desc;
			return f.good();
		}
		void display(std::ostream& os) const {
			os << std::setw(FWC) << code << std::setw(FWD)
				<< desc << std::endl;
		}
	};

	// holds a product code and the current price
	struct Price {
		unsigned code;
		double price;

		bool load(std::ifstream& f) {
			f >> code >> price;
			return f.good();
		}
		void display(std::ostream& os) const {
			os << std::setw(FWC) << code << std::setw(FWP)
				<< price << std::endl;
		}
	};

	//  holds a user-friendly description and the current price of a product
	struct Product {
		std::string desc;
		double price;

		Product() {}
		Product(const std::string& str, double p) : desc(str), price(p) {}
		void display(std::ostream& os) const {
			os << std::setw(FWD) << desc << std::setw(FWP)
				<< price << std::endl;
		}
		
		void validate() const {
			if (price < 0.0)
				throw "*** Negative prices are invalid ***";
		}
	};
}