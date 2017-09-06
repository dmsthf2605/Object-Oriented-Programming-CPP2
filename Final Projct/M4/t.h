#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Task{
	string taskName, taskSlots, taskPass, taskFail;
	public:
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
		void IntegrityCheck();
};
