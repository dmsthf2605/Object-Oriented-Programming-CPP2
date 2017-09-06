/*
OOP345 Workshop 10 - Multi-Threading
Name           : Eunsol Lee
Date           : November 24(Thu)
Student Number : 029-557-154
*/

#include <iostream>

namespace w10 {

	// holds the encryption/decryption logic used by the Securedata class
	class Cryptor {
	public:
		char operator()(char in, char key) const { return in ^ key; }
	};
	void converter(char*, char, int, const Cryptor&);

	// holds text in encoded form along with the number of bytes in the text including
	// the null terminator
	class SecureData {
		char* text;
		int nbytes;
		bool encoded;
		void code(char);
	public:
		SecureData(const char*, char);
		SecureData(const SecureData&) = delete;
		SecureData& operator=(const SecureData&) = delete;
		~SecureData();
		void display(std::ostream&) const;
		void backup(const char*);
		void restore(const char*, char);
	};
	std::ostream& operator<<(std::ostream&, const SecureData&);
}