#pragma once
enum PassType { STUDENT_PASS, ADULT_PASS, PASS_COUNT };

using namespace std;

namespace w2{	

	// holds information about the monthly passes for sale at a monitored Subway Station
	class Station{
		std::string name;
		unsigned passes[PASS_COUNT];

	public:
		Station();// default constructor
		Station(istream& is);
		void set(const std::string& n, unsigned s, unsigned a);
		void update(PassType pt, int change);
		unsigned inStock(PassType pt) const;
		const string& getName() const;
		void update();
		void restock();
		void report();
	}; // class Station

}