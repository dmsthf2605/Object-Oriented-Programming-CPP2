#pragma once
#include <iostream>
#include "Station.h"

namespace w2{

	//processes info about the monthly passes stored at a set of monitored Subway Stations
	class Stations{
		char* filename; 
		int stationCount;
		Station* stationTable;

	public: 
		Stations(char* f);
		~Stations();
		void update();
		void restock();
		void report();

	}; // class Stations
}
