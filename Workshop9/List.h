/*
OOP345 Workshop 9 - Smart Pointers
Name           : Eunsol Lee
Date           : November 16, 2016(Sun)
Student Number : 029-557-154
*/

#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>

namespace w9 {
	// defines a class that retrieves a list of types stored in a text file, 
	// holds the elements in an STL vector, provides access to them by index and displays them to an output stream
	template <typename T>
	class List {
		std::vector<T> list;

	public:
		List() { }

		List(const char* fn) {
			std::ifstream file(fn);
			if (!file)
				throw std::string("*** Failed to open file ") +
				std::string(fn) + std::string(" ***");
			while (file) {
				T e;
				if (e.load(file))
					list.push_back(*new T(e));
			}
		}
		size_t size() const { return list.size(); }

		const T& operator[](size_t i) const { return list[i]; }

		/*void operator+=(T* p) {
			list.push_back(*p);
		}*/
		void operator+=(const std::unique_ptr<T>& p) {
			list.push_back(*p);
		}

		void display(std::ostream& os) const {
			os << std::fixed << std::setprecision(2);
			for (auto& e : list)
				e.display(os);
		}
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const List<T>& l) {
		l.display(os);
		return os;
	}
}