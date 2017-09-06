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

// Item references an installer and a remover task
class Item{
	// An item has either 4 or 5 fields
	// 'item name', 'installer task', 'remover task', 'sequential code', optional 'description'
	string itemName, itemInstallerTask, itemRemoverTask, itemSequence, itemDescription;

	public:
		~Item(){ }

		// if there is only 1 field, 'slots' defaults to "1"
		Item(vector<string>& row) : itemInstallerTask("1"){
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

		void ItemPrint(){
			cout 
			<< "<" << itemName << ">" 
			<< "<" << itemInstallerTask << ">" 
			<< "<" << itemRemoverTask << ">"
			<< "<" << itemSequence << ">"
			<< "<" << itemDescription << ">\n";
		}

		// writes the item data in graphviz format to a file
		void ItemGraph(fstream& os){
			os << '"' << "Item " << itemName << '"'
			   << "->" 
			   << '"' << "Installer " << itemInstallerTask << '"' << "[color=green];\n";

			os << '"' << "Item " << itemName << '"'
			   << "->"
			   << '"' << "Remover " << itemRemoverTask << '"' << "[color=red];\n";
		} // ItemGraph
};

// contains (composition) a list of all item instances
class ItemManager{
	vector<Item> itemList;
	
	public:
		~ItemManager(){	}

		ItemManager(vector< vector <string> >& csvData){
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

		void ItemPrint(){
			int itemNumber = 0;
			for(auto i : itemList){
				itemNumber++;
				cout << "Item " << itemNumber << " ";
				i.ItemPrint();
			}
		}

		void ItemGraph(string& filename){
			fstream os(filename + ".gv", ios::out);
			os << "digraph itemGraph {\n";
			for (auto i : itemList){
				i.ItemGraph(os);
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
		std::cerr << "Usage: " << argv[0] << " itemfile.dat(a csv file) delimeter-char\n";
		return 1;
	}

	if (argc > 1) filename = argv[1];
	if (argc > 2) delimeter = argv[2][0];

	std::vector< std::vector <std::string> > csvItemData;

	csvRead(filename, delimeter, csvItemData);

	// csvPrint(csvItemData);

	ItemManager im(csvItemData);
	im.ItemPrint();
	im.ItemGraph(filename);

	return 0;
} // main()
