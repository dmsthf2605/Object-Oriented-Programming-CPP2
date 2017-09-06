#include <iostream>
#include "process.h"
#include "CString.h"

void process(char* s){
	w1::CString cs(s);
	std::cout << cs << "\n";
}