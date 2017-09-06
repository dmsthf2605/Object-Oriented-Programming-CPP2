/*
OOP345 workshop 7 - STL Containers
Name           : Eunsol Lee
Date           : November 6th, 2016(Sun)
Student Number : 029-557-154
*/

#pragma once
#include <iostream>
#include <fstream>

namespace w7 {

	// hierachy - each object describes a single product sold to the customer
	class iProduct {
	public:
		virtual double getCharge() const = 0;
		virtual void display(std::ostream&) const = 0;
	};

	class Product : public iProduct{
	protected:
		int pNum;
		double cost;
	public:
		Product(int p, double c);
		void display(std::ostream&) const;
		double getCharge() const;
	};

	class TaxableProduct : public Product{
		char tax;
		static double ptax[2];
	public:
		TaxableProduct(int p, double c, char t);
		void display(std::ostream&) const;
		double getCharge() const;
	};

	std::ostream& operator<<(std::ostream& os, const iProduct& p);
	iProduct* readProduct(std::ifstream& is);
} // namespace w7

