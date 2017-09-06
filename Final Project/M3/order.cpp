/*
OOP345 Milestone 3
Name           : Eunsol Lee
Date           : November 20, 2016(Sun)
Student Number : 029-557-154
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "util.h"

using namespace std;

// A order record must have at least three fields
// a customer name and a product name followed by a variable number of items
class Order{
	string orderCustomer, orderProduct;
	vector<string> orderItems;

	public:
		~Order(){ }

		// if there is only 1 field, 'slots' defaults to "1"
		Order(vector<string>& row){
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

		void OrderPrint(){
			cout << "<" << orderCustomer << ">"
				 << "<" << orderProduct << ">";
				 for (auto e : orderItems)
					cout << "<" << e << ">";
				 cout << "\n";
		}

		// writes the order data in graphviz format to a file
		void OrderGraph(fstream& os){
			for (auto e : orderItems)
				os << '"' << orderCustomer << " - " << orderProduct << '"'
				   << "->"
				   << '"' << e << '"' << "[color=blue];\n";
		} // OrderGraph
};

// contains (composition) a list of all order instances
class OrderManager{
	vector<Order> orderList;
	
	public:
		~OrderManager(){	}

		OrderManager(vector< vector <string> >& csvData){
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

		void OrderPrint(){
			int orderNumber = 0;
			for(auto o : orderList){
				orderNumber++;
				cout << "Order " << orderNumber << " ";
				o.OrderPrint();
			}
		}

		void OrderGraph(string& filename){
			fstream os(filename + ".gv", ios::out);
			os << "digraph orderGraph {\n";
			for (auto o : orderList){
				o.OrderGraph(os);
			}
			os << "}|n";
			os.close();
			string cmd = string("dot -Tpng ") + filename + ".gv > " + filename + ".gv.png";
			system(cmd.c_str());
		}		
};

int main(int argc, char** argv){
	string filename;
	char delimeter;

	if (argc != 3){
		std::cerr << "Usage: " << argv[0] << " orderfile.dat(a csv file) delimeter-char\n";
		return 1;
	}

	if (argc > 1) filename = argv[1];
	if (argc > 2) delimeter = argv[2][0];

	std::vector< std::vector <std::string> > csvOrderData;

	csvRead(filename, delimeter, csvOrderData);

	// csvPrint(csvOrderData);

	OrderManager om(csvOrderData);
	om.OrderPrint();
	om.OrderGraph(filename);

	return 0;
} // main()
