#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <iomanip>
#include "Station.h"
using namespace std;

namespace w2{
	Station::Station(){};// default constructor

	Station::Station(istream& is){
		string line;
		getline(is, line);
		//cout << "Station-->" << line << "<--\n";

		size_t index = 0;
		string n; // station name
		for (; index < line.size(); index++){
			if (line[index] == ';')
				break;
			n += line[index];
		}
		if (line[index] != ';'){
			cerr << "missing ';' for stationd data -->" << line << "<--\n";
			exit(4);
		}
		index++; // skip ';'
		//cout << "Station name = " << n << "\n";

		// Get the number of Student pass
		unsigned s = 0;
		for (; index < line.size(); index++){
			if (isdigit(line[index])){
				s = 10 * s + (line[index] - '0'); // '0' = 48
			}
			else if (line[index] == ' '){
				index++;
				break;
			}
			else {
				cerr << "non digit'" << line[index]
					<< "' in student pass -->" << line << "<--\n";
				exit(5);
			}
		} // for()
		//cout << "Student Pass Count : " << s << "\n";


		// Get the number of Adult pass
		unsigned a = 0;
		for (; index < line.size(); index++){
			if (isdigit(line[index])){
				a = 10 * a + (line[index] - '0');
			}
			else {
				cerr << "non digit '" << line[index]
					<< "' in adult pass  -->" << line << "<--\n";
				exit(6);
			}
		} // for()

		//cout << "adult count = " << a << "\n";
		set(n, s, a);
	}

	void Station::set(const std::string& n, unsigned s, unsigned a)
	{ // sets the instance variabls to the values received in its parameters
		name = n;
		passes[STUDENT_PASS] = s;
		passes[ADULT_PASS] = a;
	}

	void Station::update(PassType pt, int change)
	{ // updates the number of passes - sold if negative, added if positive
		passes[pt] += change;
	}

	unsigned Station::inStock(PassType pt) const
	{ // returns the number of passes of the requested type
		return passes[pt];
	}

	const string& Station::getName() const
	{ // returns a reference to a string object holding the name of the station 
		return name;
	}

	void Station::update()
	{
		int s, a;
		cout << getName() << "\n";
		cout << " Student Passes sold : "; cin >> s;
		cout << " Adudt   Passes sold : "; cin >> a;
		update(STUDENT_PASS, -s);
		update(ADULT_PASS, -a);
	}

	void Station::restock()
	{
		int s, a;
		cout << getName() << "\n";
		cout << " Student Passes added : "; cin >> s;
		cout << " Adudt   Passes added : "; cin >> a;
		update(STUDENT_PASS, s);
		update(ADULT_PASS, a);
	}

	void Station::report()
	{
		cout << setw(17) << left << getName() << right << setw(8) << inStock(STUDENT_PASS) << setw(6)
			<< inStock(ADULT_PASS) << "\n";
	}

}