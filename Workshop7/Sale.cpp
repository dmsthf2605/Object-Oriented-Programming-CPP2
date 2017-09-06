/*
OOP345 workshop 7 - STL Containers
Name           : Eunsol Lee
Date           : November 6th, 2016(Sun)
Student Number : 029-557-154
*/

// holds information about the set of products sold to a customer
#include "Sale.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

namespace w7{
	// copies the product information into an STL container
	Sale::Sale(char* filename){
		try{
			ifstream is(filename);
			if (is.fail())
				// If the object cannot open the file, throws an exception with a suitable message
				throw "Cannot open the file";
			else {
				while (is){
					pList.push_back(readProduct(is));
				}
			}			
		} 
		catch (ifstream::failure fail){
			cerr << "Cannot open the file";
		}
	}
	
	// The output includes column headings and the total sale amount including taxes paid.  
	// The product number and cost occupy fields of width 10
	void Sale::display(std::ostream& os) const{
		double total = 0;
		os << setw(10) << "Product No" << setw(10) << "Cost" << " Taxable\n";
		os << fixed << setprecision(2);

		for (auto p : pList){
			os << *p;
			total += p->getCharge();
		}
		os << setw(10) << "Total" << fixed << setprecision(2) << setw(10) << total << '\n';
	}
}