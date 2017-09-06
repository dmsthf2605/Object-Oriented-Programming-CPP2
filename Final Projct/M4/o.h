/*
OOP345 Milestone 4
Name           : Eunsol Lee
Date           : November 27, 2016(Sun)
Student Number : 029-557-154
*/

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "util.h"
#include "i.h"

using namespace std;

class Order{
	string orderCustomer, orderProduct;
	vector<string> orderItems;

	public:
		~Order();
		Order(vector<string>& row);
		void OrderPrint();
		void OrderGraph(fstream& os);
		size_t size() { return orderItems.size(); }
		string& getItem(int i){ return orderItems[i]; }
		string& getCustomerName(){ return orderCustomer; }
};

class OrderManager{
	vector<Order> orderList;

	public:
		~OrderManager();
		OrderManager(vector< vector <string> >& csvData);
		void OrderPrint();
		void OrderGraph(string& filename);
		string& getOrderItem(int, int);
		void IntegrityCheck(ItemManager& im);
};
