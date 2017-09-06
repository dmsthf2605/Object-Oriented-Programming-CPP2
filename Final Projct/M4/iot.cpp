/*
OOP345 Milestone 4
Name           : Eunsol Lee
Date           : November 27, 2016(Sun)
Student Number : 029-557-154
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "util.h"
#include "i.h"
#include "o.h"
#include "t.h"

using namespace std;

int main(int argc, char** argv){

	string filename;
	char delimeter;

	try{
	if (argc != 5)
		std::cerr << "Usage: " << argv[0] << " itemfile.dat orderfile.dat taskfile.dat(all csv file) delimiter-char\n";

	string filenameItem = argv[1]; // 1st arg
	string filenameOrder = argv[2]; // 2nd arg
	string filenameTask = argv[3]; // 3rd arg
	char delim = argv[4][0]; // 4th, 1st char

	std::vector< std::vector <std::string> > csvItemData;
	std::vector< std::vector <std::string> > csvOrderData;
	std::vector< std::vector <std::string> > csvTaskData;

	csvRead(filenameItem, delim, csvItemData);
	csvRead(filenameOrder, delim, csvOrderData);
	csvRead(filenameTask, delim, csvTaskData);

	// csvPrint(csvItemData);

	ItemManager im(csvItemData);
	im.ItemPrint();
	im.ItemGraph(filenameItem);

	OrderManager om(csvOrderData);
	om.OrderPrint();
	om.OrderGraph(filenameOrder);

	TaskManager tm(csvTaskData);
	tm.TaskPrint();
	tm.TaskGraph(filenameTask);

	
	bool GoodToGo = true;
	cout << "Checking Task Integrity\n";
		try{
			tm.IntegrityCheck();
		} catch (string& e){
			GoodToGo = false;
			cerr << e << "\n";
		}	
		
	cout << "Checking Item Integrity\n";
		try{
			im.IntegrityCheck(tm);
		}
		catch (string& e){
			GoodToGo = false;
			cerr << e << "\n";
		}

	cout << "Checking Order Integrity\n";
		try{
			om.IntegrityCheck(im);
		}
		catch (string& e){
			GoodToGo = false;
			cerr << e << "\n";
		}

	} catch (string& e){
		cerr << e << "\n";
	}

	return 0;
} 
