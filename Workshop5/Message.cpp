/*
OOP345 workshop 5
Name           : Eunsol Lee
Date           : October 24, 2016(Mon)
Student Number : 029-557-154
*/

#include "Message.h"
#include <string>
#include <iostream>

using namespace std;

namespace w5{

	Message::Message(std::ifstream& in, char c){
		/* constructor retrieves a record from the in file object,
		parses the record(as described above) and stores its components in the Message object.
		c is the character that delimits each record*/

		std::string line;
		getline(in, line, c);
		auto cr = line.find('\r'); // go to beginning of the line
		if (cr != std::string::npos)
			line.erase(cr);
		//std::cout << "line -->" << line << "<--\n";

		size_t i = 0;
		while (i < line.size() && line[i] != ' '){
			user += line[i];
			i++;
		} // while()
		i++; // skip ' '
		//std::cout << "user = " << user << "\n";

		if (i < line.size() && line[i] == '@'){
			i++; // skip @
			while (i < line.size() && line[i] != ' '){
				reply += line[i];
				i++;
			} // while()
			i++; // skip ' '
			//std::cout << "reply = " << reply << "\n";
		} // if(i < line.size() && line[i] == '@')

		// copy remainder of line to 'tweet'
		while (i < line.size()){
			tweet += line[i];
			i++;
		}
		//std::cout << "tweet = " << tweet << "\n";
	}

	bool Message::empty() const{ // returns true if the object is in a safe empty state
		return tweet.empty();
	}

	void Message::display(std::ostream& os) const{ // displays the Message objects within the container
		os << "Message\n";
		os << " User  : " << user << "\n";
		if (!reply.empty()){
			os << " Reply : " << reply << "\n";
		}
		os << " Tweet : " << tweet << "\n";
		os << "\n";
	}

}
