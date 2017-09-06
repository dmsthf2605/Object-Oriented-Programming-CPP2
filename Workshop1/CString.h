#include <iostream>
#pragma once // guards against repeated use

namespace w1{
	const int MAX = 3;

	class CString{
		char data_[MAX + 1];
	public:
		CString(char* data);
		void display(std::ostream& os);
	};

	std::ostream& operator<<(std::ostream& os, CString& cs);
}
