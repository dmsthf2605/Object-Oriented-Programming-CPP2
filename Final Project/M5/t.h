/*
OOP345 Milestone 5
Name           : Eunsol Lee
Date           : December 8th(Thursday)
Student Number : 029-557-154
*/

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Task{
	string taskName, taskSlots, taskPass, taskFail;
	int count;
	public:
		Task(){}
		~Task();
		Task(vector<string>& row);
		void TaskPrint();
		void TaskGraph(fstream& os);			
		string& getTaskName(){ return taskName; }
		string& getTaskPass(){ return taskPass; }
		string& getTaskFail(){ return taskFail; }
};

class TaskManager{
	vector<Task> taskList;
	
	public:
		~TaskManager();
		TaskManager(vector< vector <string> >& csvData);
		void TaskPrint();
		void TaskGraph(string& filename);
		Task* TaskFind(string& name);
		size_t getSize() { return taskList.size(); }
		Task* getTask(size_t i){ return &taskList[i]; }
		void IntegrityCheck();
};
