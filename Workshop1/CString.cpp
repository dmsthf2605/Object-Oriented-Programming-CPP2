#include <iostream>
#include <cstring>
#include "CString.h"

namespace w1{
	CString::CString(char* data){
		if (!data){
			data_[0] = '\0';
		} else {
			strncpy(data_, data, MAX);
			data_[MAX] = '\0';
		}
	}

	void CString::display(std::ostream& os){
		os << data_;
	}
	
	std::ostream& operator<<(std::ostream& os, CString& cs){
		static int c = 0;
		os << c << ":";
		c++;
		cs.display(os);
		return os;
	}
}

