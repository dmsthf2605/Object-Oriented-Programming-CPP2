/*
OOP345 workshop 7 - STL Containers
Name           : Eunsol Lee
Date           : November 6th, 2016(Sun)
Student Number : 029-557-154
*/

#include "iProduct.h"
#include <iomanip>
#include <iostream>
using namespace std;

namespace w7{
	// holds information about a product that consists of its product number and its cost
	Product::Product(int p, double c){
		pNum = p;
		cost = c;
	}

	// returns the price chargable to the customer
	double Product::getCharge() const{
		return cost;
	}

	// inserts the product information in the form of a single line into the output stream
	void Product::display(std::ostream& os) const{
		os << setw(10) << right << pNum << setw(10) << setprecision(2) << cost << "\n";
	}

	// derives from Product and holds additional information about the product's taxable status
	TaxableProduct::TaxableProduct(int p, double c, char t) : Product(p, c){
		tax = t;
	}

	double TaxableProduct::ptax[2] = { 1.13, 1.08 };

	// Use a class array (an array of class variables)  to store the tax rates for HST and PST tax codes (13% and 8%). 
	double TaxableProduct::getCharge() const{
		double t = 1;
		if (tax == 'H') t = ptax[0];
		if (tax == 'P') t = ptax[1];
		return cost * t;
	}

	void TaxableProduct::display(std::ostream& os) const{
		os << setw(10) << right << pNum << setw(10) << setprecision(2) << cost << " ";
		if (tax == 'H') os << "HST";
		if (tax == 'P') os << "PST";
		os << "\n";
	}

	// displays the product information in the form of a single line on the output stream
	std::ostream& operator<<(std::ostream& os, const iProduct& p){
		p.display(os);
		return os;
	}

	iProduct* readProduct(std::ifstream& is){
		int p;
		double c;
		char t;
		iProduct* temp;

		// reads the next record from the stream
		is >> p >> c;
		
		// A non-taxable record terminates with a newline character immediately following the price field
		if (is.get() != '\n'){
			is.get(t);
			// allocates memory for the corresponding iProduct object
			// copies the record information into that object
			temp = new TaxableProduct(p, c, t);
		}
		else {
			temp = new Product(p, c);
		}

		// returns its address to the caller function
		return temp;
	}
}

