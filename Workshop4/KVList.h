/*
OOP345 workshop4
Name           : Eunsol Lee
Date           : October 5, 2016(Wed)
Student Number : 029-557-154
*/

#pragma once
#include <utility> // std::pair
#include <vector>

using namespace std;

template <typename K, typename V, int N>
class KVList{
	size_t count;
	//K k[N];
	//V v[N];
	//std::pair<K, V> table[N];
	vector<K> keys;
	vector<V> values;	

	public:
		//default constructor - adopts a safe empty state
		KVList() : count(0){}
		
		// returns the number of entires in the key-value list
		size_t size() const{ return count; } 
		
		// returns an unmodifiable reference to the key of element i in the list
		const K& key(int i) const
		{
			//if (i >= 0 && i < N) return k[i];
			//if (i >= 0 && i < N) return table[i].first;
			if (i >= 0 && i < N) return keys.at(i);
		} 

		// returns an unmodifiable reference to the value of element i in the list
		const V& value(int i) const
		{
			//if (i >= 0 && i < N) return v[i];
			//if (i >= 0 && i < N) return table[i].second;
			if (i >= 0 && i < N) return values.at(i);
		} 

		// adds a new element to the list if room exists 
		// and returns a reference to the current object, 
		// does nothing if no room exists
		KVList& add(const K& kk, const V& vv)
		{
			if (count < N){
				//k[count] = kk;
				//v[count] = vv;
				//table[count] = std::make_pair(kk, vv);
				keys.push_back(kk);
				values.push_back(vv);
				count++;
			}
			return *this;
		} 

		// returns the index of the first element in the list with a key equal to kk - defaults to 0
		int find(const K& kk) const
		{
			int i = 0;
			for (auto it = keys.begin(); it != keys.end(); ++it, ++i){
				if ((*it) == kk){
					return i;
				}
			}

			/*for (size_t i = 0; i < count; i++){
				//if (k[i] == kk) 
				if (table[i].first == kk)
					return i;
			}*/
			return 0;
		} 	

		// replaces element i in the list with the key and value received 
		// and returns a reference to the current object
		KVList& replace(int i, const K& kk, const V& vv)
		{
			if (i >= 0 && i < count){
				//k[i] == kk;
				//v[i] == vv;
				//table[i] = std::make_pair(kk, vv);
				keys.at(i) = kk;
				values.at(i) = vv;
			}
	
			return *this;
		} 
	
}; // class KVList

