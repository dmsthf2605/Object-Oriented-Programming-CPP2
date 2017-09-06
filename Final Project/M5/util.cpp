/*
OOP345 Milestone 5
Name           : Eunsol Lee
Date           : December 8th(Thursday)
Student Number : 029-557-154
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"

using namespace std;

// Splitting each line in a vector of string fields.  
// Trim leading and trailing spaces ' ' from each field
void trim(string& field){
	// delete leading spaces
	while (!field.empty() && field[0] == ' '){
		field.erase(0, 1);
	}
	// delete trailing spaces
	while (!field.empty() && field[field.size() - 1] == ' '){
		field.erase(field.size() - 1, 1);
	}
}

// Read the file, line, by line
void csvRead(string& filename, char delimeter, vector< vector<string> >& csvData){
	string line;
	vector < string > fields;
	ifstream is(filename);

	if (!is.is_open()){
		// If the object cannot open the file, throws an exception with a suitable message
		cout << "cannot open file " << filename;
	}
	else {
		while (getline(is, line)){
			auto cr = line.find('\r');
			if (cr != string::npos){
				line.erase(cr, 1);
			}

			string field;
			size_t i = 0;
			while (i < line.size()){
				if (line[i] != delimeter){
					field += line[i];
				}
				else { // found delimeter
					trim(field);
					// add field to the list of fields
					fields.push_back(move(field));
				}
				i++;
			}

			if (!field.empty()){
				trim(field);
				fields.push_back(move(field));
			}

			// Store the vector of string fields into a vector of lines
			csvData.push_back(move(fields));
		} // while(getline(is, line))
		is.close();
	}
} // csvRead()

// Print the csvData out three ways using indices, iterators, and range-based for loops
void csvPrint(vector < vector<string> >& csvData){
	cout << "number of lines = " << csvData.size() << "\n";

	// indices
	cout << "Print using indices\n";
	for (size_t row = 0; row < csvData.size(); row++){
		cout << "row = " << row << " ";
		for (size_t column = 0; column < csvData[row].size(); column++){
			cout << "'" << csvData[row][column] << "' ";
		}
		cout << "\n";
	}
	cout << "\n";
	// iterators
	cout << "Print using iterators\n";
	for (auto rIt = csvData.begin(); rIt != csvData.end(); rIt++){
		for (auto cIt = rIt->begin(); cIt != rIt->end(); cIt++){
			cout << "{" << *cIt << "} ";
		}
		cout << "\n";
	}
	cout << "\n";
	// range-based for loops
	cout << "Print using range-based for loops\n";
	for (auto row : csvData){
		for (auto column : row){
			cout << "[" << column << "] ";
		}
		cout << "\n";
	}
} // csvPrint()


// task name starts with an alpha or _ character
// followd by alphas, digits, spaces, '-' or '_'
bool taskNameValid(string& s){
	// name cannot be empty string ""
	if (s.empty()) return false;
	for (auto chr : s){
		if (!(isalnum(chr) || chr == ' ' || chr == '_' || chr == '-'))
			return false;
	}
	return true;
}

// field slot is an integer ( one or more digits 0-9)
bool taskSlotValid(string& s){
	for (auto chr : s){
		if (!(isdigit(chr)))
			return false;
	}
	return true;
}

bool itemNameValid(string& s){
	if (s.empty()) return false;
	for (auto chr : s){
		if (!(isalnum(chr) || chr == ' ' || chr == '_' || chr == '-'))
			return false;
	}
	return true;
}

bool itemSequenceValid(string& s){
	for (auto chr : s){
		if (!(isdigit(chr)))
			return false;
	}
	return true;
}

bool validProductName(string& s){
	if (s.empty()) return false;
	for (auto chr : s){
		if (!(isalnum(chr) || chr == ' ' || chr == '_'))
			return false;
	}
	return true;
}

bool validCustomerName(string& s){
	if (s.empty()) return false;
	for (auto chr : s){
		if (!(isalnum(chr) || chr == ' ' || chr == '\'' || chr == '-'))
			return false;
	}
	return true;
}