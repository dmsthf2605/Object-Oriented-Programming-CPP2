#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "util.h"
#include "i.h"

using namespace std;

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
