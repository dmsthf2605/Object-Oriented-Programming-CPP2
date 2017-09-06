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

using namespace std;

	Item::~Item(){ }

	Item::Item(vector<string>& row) : itemInstallerTask("1"){
			switch(row.size()){
			case 5:
				// description can be anything 
				itemDescription = row[4];
			case 4:
				if (itemSequenceValid(row[3]))
					itemSequence = row[3];
				else 
					throw string("expected item sequence number, found -->") + row[3] + "<--";
			case 3:
				if (taskNameValid(row[2]))
					itemRemoverTask = row[2];
				else
					throw string("expected remover task, found -->") + row[2] + "<--";
			case 2:
				if (taskNameValid(row[1]))
					itemInstallerTask = row[1];
				else 
					throw string("expected intsaller task , found -->") + row[1] + "<--";
			case 1:	
				if(itemNameValid(row[0]))	
					itemName = row[0];
				else 
					throw string("expected item name, found -->") + row[0] + "<--";
				break;
	
			default:
				throw string("Expected 4 or 5 feilds, found ") + to_string(row.size());
		}	
	}

	void Item::ItemPrint(){
			cout 
			<< "<" << itemName << ">" 
			<< "<" << itemInstallerTask << ">" 
			<< "<" << itemRemoverTask << ">"
			<< "<" << itemSequence << ">"
			<< "<" << itemDescription << ">\n";
		}

	// writes the item data in graphviz format to a file
	void Item::ItemGraph(fstream& os){
		os << '"' << "Item " << itemName << '"'
		   << "->" 
		   << '"' << "Installer " << itemInstallerTask << '"' << "[color=green];\n";
		
		os << '"' << "Item " << itemName << '"'
		   << "->"
		   << '"' << "Remover " << itemRemoverTask << '"' << "[color=red];\n";
	} // ItemGraph

	ItemManager::~ItemManager(){	}

	ItemManager::ItemManager(vector< vector <string> >& csvData){
		int lineNumber = 0;
		for (auto row : csvData){
			try{
				lineNumber++;
				itemList.push_back(move(Item(row)));
			}
			catch (string& e){
				cerr << "Item could not understand line" << lineNumber << ": " << e << "\n";
			}
		}
	}

	void ItemManager::ItemPrint(){
		int itemNumber = 0;
		for(auto i : itemList){
			itemNumber++;
			cout << "Item " << itemNumber << " ";
			i.ItemPrint();
		}
	}

	void ItemManager::ItemGraph(string& filename){
		fstream os(filename + ".gv", ios::out);
		os << "digraph itemGraph {\n";
		for (auto i : itemList){
			i.ItemGraph(os);
		}
		os << "}|n";
		os.close();
		string cmd = string("dot -Tpng ") + filename + ".gv > " + filename + ".gv.png";
		cout << "running->" << cmd << "\n";
		system(cmd.c_str());
		cout << "\n";
	}		

	Item* ItemManager::ItemFind(string& name){
		for (size_t i = 0; i < itemList.size(); i++){
			if (itemList[i].getItemName() == name)
				return &itemList[i];
		}
		return nullptr; // not found
	}

	void ItemManager::IntegrityCheck(TaskManager& tm){
		for (auto i : itemList){
			if (tm.TaskFind(i.getItemInstallerTask()) == nullptr)
				throw string("Item '") + i.getItemName() + "' referenced Installer task '" + i.getItemInstallerTask() + "' but it does not exist";
			if (tm.TaskFind(i.getItemRemoverTask()) == nullptr)
				throw string("Item '") + i.getItemName() + "' referenced Remover task '" + i.getItemRemoverTask() + "' but it does not exist";
		}
	}