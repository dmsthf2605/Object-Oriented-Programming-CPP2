/*
OOP345 workshop3
Name           : Eunsol Lee
Date           : October 2, 2016(Sun)
Student Number : 029-557-154

*/

#pragma once // the year is > 1977
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

namespace w3{

	class Text{
		string* lineTable;
		size_t  count;

	public:
		// returns the number of records of text data
		size_t size() const{
			return count;
		}

		void print()
		{
			for (size_t i = 0; i < count; i++)
			{
				cout << i+1 << ":-->" << lineTable[i] << "<--\n";
			}
		}

		// create a 'zombie'
		Text() : count(0), lineTable(nullptr){}
		
		~Text() { delete[] lineTable; }

		Text(char* filename) : count(0), lineTable(nullptr)
		{
			// open the file
			fstream is(filename, ios::in);
			if (is.is_open()){
				string line;
				while (getline(is, line)){
					count++;
				}
				// cout << "file '" << filename << "' has " << count << " lines\n";

				lineTable = new string [count];

				// read the file
				is.clear(); // reset the END-OF-FILE error state
				is.seekg(0, ios_base::beg); // position file at the beginning

				for (size_t i = 0; i < count; i++){
					getline(is, lineTable[i]);
					auto cr = lineTable[i].find('\r');
					if (cr != string::npos){
						lineTable[i].erase(cr);
					}
				}

				is.close();
				// print();

			} else {
				cerr << "Cannot open file -->" << filename << "<--\n";
				exit(1);
			}		
		} // one argument constructor*/

		// ---- Rule of three ----
		// a copy constructor
		Text(const Text& rhs) : count(0), lineTable(nullptr)
		{
			*this = rhs;
		}

		// a copy assignment operator
		Text& operator=(const Text& rhs)
		{
			if (this != &rhs){
				delete [] lineTable;
				count     = rhs.count;
				lineTable = new string [count];
				// deep copying
				for (size_t i = 0; i < count; i++){
					lineTable[i] = rhs.lineTable[i];
				}
			}
			return *this;
		}

		// ---- Rule of five ----
		// a move constructor
		Text(Text&& rhs) : count(0), lineTable(nullptr)
		{
			*this = move(rhs);
		}

		// a move assignment operator
		Text&& operator=(Text&& rhs)
		{
			if (this != &rhs){
				delete[] lineTable;

				// steal the brain
				count     = rhs.count;
				lineTable = rhs.lineTable;

				// turn rhs into a 'Zombi' 
				rhs.count     = 0;
				rhs.lineTable = nullptr;
			}
			return move(*this); // think as it r-value
		}
		
		
	};

}