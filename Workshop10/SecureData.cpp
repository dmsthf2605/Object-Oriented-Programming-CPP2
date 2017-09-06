/*
OOP345 Workshop 10 - Multi-Threading
Name           : Eunsol Lee
Date           : November 24(Thu)
Student Number : 029-557-154
*/

#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <thread>
#include <vector>
#include "SecureData.h"

namespace w10 {

	void converter(char* t, char key, int n, const Cryptor& c) {
		for (int i = 0; i < n; i++)
			t[i] = c(t[i], key);
	}

	SecureData::SecureData(const char* file, char key) {
		// open text file
		std::fstream input(file, std::ios::in);
		if (!input)
			throw std::string("\n***Failed to open file ") +
			std::string(file) + std::string(" ***\n");

		// copy from file into memory
		nbytes = 0;
		input >> std::noskipws;
		while (input.good()) {
			char c;
			input >> c;
			nbytes++;
		}
		nbytes--;
		input.clear();
		input.seekg(0, std::ios::beg);
		text = new char[nbytes + 1];

		int i = 0;
		while (input.good())
			input >> text[i++];
		text[--i] = '\0';
		std::cout << "\n" << nbytes << " bytes copied from text "
			<< file << " into memory (null byte added)\n";
		encoded = false;

		// encode using key
		code(key);
		std::cout << "Data encrypted in memory\n";
	}

	SecureData::~SecureData() {
		delete[] text;
	}

	void SecureData::display(std::ostream& os) const {
		if (text && !encoded)
			os << text << std::endl;
		else if (encoded)
			throw std::string("\n***Data is encoded***\n");
		else
			throw std::string("\n***No data stored***\n");
	}

	// Use std::bind from the functional library to bind the converter
	void SecureData::code(char key) {
		//converter(text, key, nbytes, Cryptor());
		std::thread t1(std::bind(converter, text, key, nbytes / 2, Cryptor()));
		std::thread t2(std::bind(converter, text + (nbytes / 2), key, nbytes - (nbytes / 2), Cryptor()));
		t1.join();
		t2.join();

		encoded = !encoded;
	}

	void SecureData::backup(const char* file) {
		if (!text)
			throw std::string("\n***No data stored***\n");
		else if (!encoded)
			throw std::string("\n***Data is not encoded***\n");
		else {
			// open binary file
			std::ofstream f(file, std::ios::out|std::ios::binary|std::ios::trunc);
			if (!f)
				throw std::string("\n***Failed to open file ") +
				std::string(file) + std::string(" ***\n");

			// write binary file here
			f.write(text, nbytes);
			f.close();
		}
	}

	// deallocates the existing data, determines the number of bytes to be read, 
	// allocates memory for them, and read the data from the file
	void SecureData::restore(const char* file, char key) {
		// open binary file
		std::ifstream f(file, std::ios::in|std::ios::binary);
		if (!f)
			throw std::string("\n***Failed to open file ") +
			std::string(file) + std::string(" ***\n");

		// allocate memory here
		if (text){
			delete[] text;
			text = nullptr;
		}
		text = new char[nbytes + 1];

		// read binary file here
		f.read(text, nbytes);
		f.close();

		std::cout << "\n" << nbytes + 1 << " bytes copied from binary file "
			<< file << " into memory (null byte included)\n";
		encoded = true;

		// decode using key
		code(key);
		std::cout << "Data decrypted in memory\n\n";
	}

	std::ostream& operator<<(std::ostream& os, const SecureData& sd) {
		sd.display(os);
		return os;
	}
}