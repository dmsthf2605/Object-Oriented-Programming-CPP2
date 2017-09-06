#include <iostream>
#include <vector>
#include <string>
#include "util.h"

using namespace std;

int main(int argc, char** argv){
	string filename;
	char delimeter;

	if (argc != 3){
		std::cerr << "Usage: " << argv[0] << "file delimiter-char\n";
		return 2;
	}

	// Pick up the filename and separator character from the command line
	if (argc > 1) filename = argv[1];
	if (argc > 2) delimeter = argv[2][0];

	// 2d array: csvData[line][field]
	std::vector< std::vector <std::string> > csvData;

	csvRead(filename, delimeter, csvData);

	// print
	csvPrint(csvData);

	return 0;
} // main()