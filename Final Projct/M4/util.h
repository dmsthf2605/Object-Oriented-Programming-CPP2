/*
OOP345 Milestone 4
Name           : Eunsol Lee
Date           : November 27, 2016(Sun)
Student Number : 029-557-154
*/

#pragma once
#include <vector>
#include <string>

using namespace std;

void trim(string& field);
void csvRead(string& filename, char delimeter, vector< vector<string> >& csvData);
void csvPrint(vector < vector<string> >& csvData);

// 
bool taskNameValid(string& s);
bool taskSlotValid(string& s);
bool itemNameValid(string& s);
bool itemSequenceValid(string& s);
bool validProductName(string& s);
bool validCustomerName(string& s);
