#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "util.h"
#include "o.h"

using namespace std;

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
