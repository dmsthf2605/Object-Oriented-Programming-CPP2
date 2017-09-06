/*
OOP345 Milestone 2
Name           : Eunsol Lee
Date           : November 13, 2016(Sun)
Student Number : 029-557-154
*/

#pragma once
#include <vector>
#include <string>

using namespace std;

void trim(string& field);
void csvRead(string& filename, char delimeter, vector< vector<string> >& csvData);
void csvPrint(vector < vector<string> >& csvData);

