/*
OOP345 Milestone 5
Name           : Eunsol Lee
Date           : December 8th(Thursday)
Student Number : 029-557-154
*/

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "util.h"
#include "t.h"

using namespace std;

class Item{
	string itemName, itemInstallerTask, itemRemoverTask, itemSequence, itemDescription;

	public:
		~Item();
		Item(vector<string>& row);
		void ItemPrint();
		void ItemGraph(fstream& os);
		string& getItemInstallerTask(){ return itemInstallerTask; }
		string& getItemRemoverTask  (){ return itemRemoverTask; }
		string& getItemName         (){ return itemName; }
};

class ItemManager{
	vector<Item> itemList;

	public:
		~ItemManager();
		ItemManager(vector< vector <string> >& csvData);
		void ItemPrint();
		void ItemGraph(string& filename);		
		void IntegrityCheck(TaskManager& tm);
		Item* ItemFind(string& name);
		size_t getSize() { return itemList.size(); }
		Item* getItem(size_t i){ return &itemList[i]; }
};
