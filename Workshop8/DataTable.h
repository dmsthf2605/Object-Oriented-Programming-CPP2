/*
OOP345 Workshop 8 - STL Algorithms
Name           : Eunsol Lee
Date           : November 13, 2016(Sun)
Student Number : 029-557-154
*/

#pragma once
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <functional>

using namespace std;

namespace w8{
	template <class T>
	class DataTable {
		vector<T> _x, _y; // _x: independent value, _y: dependent
		int _fw, _nd;

	public:
		// receives a reference to the file stream that holds the data values, 
		// the field width for displaying the data and the number of decimals to display
		DataTable(ifstream& file, int fw, int nd) : _fw(fw), _nd(nd){
			T x, y;
			if (file.is_open()){
				while (file >> x >> y){
						_x.push_back(x);
						_y.push_back(y);
				}
				file.close();
			} else {
				cerr << "Cannot open the data file\n";
				exit(1);
			}
		}

		// the average of all values in the sample
		// returns the mean value of the dependent coordinate
		T mean() const{
			T s = accumulate(_y.begin(), _y.end(), (T)0);
			T n = _y.size();
			return s / n;
		}

		// the spread of the numbers away from their mean
		// returns the standard deviation of the dependent coordinates
		T sigma() const{
			T m = mean(); // mean of all values in the data set
			T n = _y.size(); // number of values in the data set
			T s = 0.0; // sum of 

			for (int i = 0; i < n; ++i)
				s += (_y[i] - m) * (_y[i] - m);	

			return sqrt(s / (n - 1));
		}

		// the middle number in the sorted set of the values 
		// (that is, the value separating the lower and upper halves of the data in a sorted set)
		// returns the median value of the dependent coordinate
		T median() const {
			T n = _y.size();
			vector<T> s = _y;
			sort(s.begin(), s.end());

			return s[n / 2];
		}

		// returns the slope and intercept for the data set
		void regression(T& slope, T& y_intercept) const{
			T n = _y.size(); // number of values in the data set
			T x = accumulate(_x.begin(), _x.end(), (T)0); // sum of first scores
			T y = accumulate(_y.begin(), _y.end(), (T)0); // sum of second scores
			T x2 = 0;
			T xy = 0;// Sum of the product of first and Second Scores
			for (int i = 0; i < n; i++){
				xy += _x[i] * _y[i];
				x2 += _x[i] * _x[i];
			}
			slope = (n * xy - x * y) / (n * x2 - x * x);
			y_intercept = (y - slope * x) / n;

		}

		// displays the data pairs
		void display(std::ostream& os) const{
			os << fixed << setprecision(_nd);
			os << setw(_fw) << right << "x" << setw(_fw) << "y\n";
			for (int i = 0; i < _x.size(); i++){
				os << setw(_fw) << right << _x[i] << setw(_fw) << _y[i] << "\n";
			}
		}
	};

	// inserts the data generated by display() into the output stream
	template <typename T>
	std::ostream& operator<<(std::ostream& os, const DataTable<T>& d){
		d.display(os);
		return os;
	}
} // namespace w8


