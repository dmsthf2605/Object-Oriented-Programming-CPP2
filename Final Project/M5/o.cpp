/*
OOP345 Milestone 5
Name           : Eunsol Lee
Date           : December 8th(Thursday)
Student Number : 029-557-154
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "util.h"
#include "o.h"

	Order::~Order(){ }

	Order::Order(vector<string>& row){
		if (row.size() < 3)
			throw string("Expected 3 feilds, found ") + to_string(row.size());

		if (validCustomerName(row[0]))
			orderCustomer = row[0];
		else
			throw string("could not undertand Customer Name -->") + row[0] + "<--";

		if (validProductName(row[1]))
			orderProduct = row[1];
		else
			throw string("could not undertand Product Name -->") + row[1] + "<--";
			
		for (size_t i = 2; i < row.size(); i++){
			if (itemNameValid(row[i]))
				orderItems.push_back(row[i]);
			else
				throw string("could not understand Item Name -->") + row[i] + "<--";
		}
	}	

	void Order::OrderPrint(){
		cout << "<" << orderCustomer << ">"
			 << "<" << orderProduct << ">";
		 for (auto e : orderItems)
			cout << "<" << e << ">";
		 cout << "\n";
	}

	void Order::OrderGraph(fstream& os){
		for (auto e : orderItems)
			os << '"' << orderCustomer << " - " << orderProduct << '"'
			   << "->"
			   << '"' << e << '"' << "[color=blue];\n";
	} // OrderGraph

	OrderManager::~OrderManager(){	}

	OrderManager::OrderManager(vector< vector <string> >& csvData){
		int lineNumber = 0;
		for (auto row : csvData){
			try{
				lineNumber++;
				orderList.push_back(move(Order(row)));
			}
			catch (string& e){
				cerr << "Order could not understand line" << lineNumber << ": " << e << "\n";
			}
		}
	}

	void OrderManager::OrderPrint(){
		int orderNumber = 0;
		for(auto o : orderList){
			orderNumber++;
			cout << "Order " << orderNumber << " ";
			o.OrderPrint();
		}
	}

	void OrderManager::OrderGraph(string& filename){

		fstream os(filename + ".gv", ios::out);
		os << "digraph orderGraph {\n";
		for (auto o : orderList){
			o.OrderGraph(os);
		}
		os << "}|n";
		os.close();
		string cmd = string("dot -Tpng ") + filename + ".gv > " + filename + ".gv.png";
		cout << "running->" << cmd << "\n";
		system(cmd.c_str());
		cout << "\n";
	}		

	/*
	string& OrderManager::getOrderItem(int od, int id){
		return orderList[od].getItem(id);
	}

	void OrderManager::IntegrityCheck(ItemManager& im){
		for (int i = 0; i < orderList.size(); i++){
			for (int j = 0; j < orderList[i].size(); j++){
				if (im.ItemFind(getOrderItem(i, j)) == nullptr)
					throw string("Item '") + getOrderItem(i, j) +"' Ordered for '" + orderList[i].getCustomerName() + "' does not exist";
			}
		}
	}	
	*/

	void OrderManager::IntegrityCheck(ItemManager& im){
		for (auto o : orderList){
			for (size_t count = 0; count < o.size(); count++){
				if (im.ItemFind(o.getItem(count)) == nullptr) // references item but item does not exist
					throw string("Order '") + o.getCustomerName() + "'/'" + o.getProductName() + "' references item '" + o.getItem(count) + "' but it does not exist";
			}
		}
	}
	