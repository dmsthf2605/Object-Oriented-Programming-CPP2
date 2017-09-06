#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <iomanip>
#include "Stations.h"

using namespace std;

namespace w2{
	//processes info about the monthly passes stored at a set of monitored Subway Stations
	Stations::Stations(char* f) : filename(f)
	{ // Receives the name of a file in char* filename
		fstream is(filename); // defines a file obj named is
		if (!is.is_open()){ // when the file is not opened show the err msg
			cerr << "Cannot open the data file -->" << filename << "<--\n";
			exit(1);
		}

		// Read the file
		string line;
		getline(is, line, ';'); // read the data until find the ';'
		// cout << "line -->" << line << "<--\n";

		bool bOK = true;
		size_t i; // unsigned data type
		// Check the first char is a number or not
		for (i = 0; i < line.size(); i++){
			if (!isdigit(line[i])){
				bOK = false;
				break;
			}
		}
		
		if (!bOK){
			cerr << "Non digit!" << line[i] << "' in station count number file -->"
				<< line << "<--\n";
			exit(2);
		}

		// store the number of stations to stationCount
		stationCount = stoi(line);
		//cout << "Station Count : " << stationCount << "\n";
		
		// skip '\n'
		getline(is, line);
		if (line.size() != 0){
			cerr << "trailing -->" << line
				<< "<-- characters after ';' in station count field\n";
			exit(3);
		}

		// allocates memory for the monitored stations
		stationTable = new Station[stationCount];
		//copy the data from the file to each Station object
		for (int s = 0; s < stationCount; s++){
			stationTable[s] = Station(is);
		}
			is.close();
	}

	Stations::~Stations(){
		delete[] stationTable;
	}

	void Stations::update()
	{ // accepts the number of passes sold and updates the data for each station in turn
		cout << "Passes Sold : \n";
		cout << "--------------\n";
		for (int s = 0; s < stationCount; s++){
			stationTable[s].update();
		}
		cout << "\n";
	}

	void Stations::restock()
	{ // accepts the number of passes added and updates the data for each station in turn
		cout << "Passes Added : \n";
		cout << "--------------\n";
		for (int s = 0; s < stationCount; s++){
			stationTable[s].restock();
		}
		cout << "\n";
	}

	void Stations::report()
	{ // reports the number of passes currently available at each station
		//cout << "Report:\n";
		cout << "Passes in Stock : Student Adult\n";
		cout << "-------------------------------\n";
		for (int s = 0; s < stationCount; s++){
			stationTable[s].report();
		}
	}

}
