/*
OOP345 Milestone 4
Name           : Eunsol Lee
Date           : November 27, 2016(Sun)
Student Number : 029-557-154
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "util.h"
#include "t.h"

using namespace std;

	Task::~Task(){ }

	// if there is only 1 field, 'slots' defaults to "1"
	Task::Task(vector<string>& row) : taskSlots("1"){
			switch(row.size()){
				case 4:
					if(taskNameValid(row[3]))
						taskFail = row[3];
					else 
						throw string("expected fail task name, found -->") + row[3] + "<--";
				case 3:
					if(taskNameValid(row[2]))
						taskPass = row[2];
					else
						throw string("expected fail task name, found -->") + row[2] + "<--";

				case 2:
					if(taskSlotValid(row[1]))
						taskSlots = row[1];
					else 
						throw string("expected fail task slot, found -->") + row[1] + "<--";

				case 1:	
					if(taskNameValid(row[0]))	
						taskName = row[0];
					else 
						throw string("expected fail task name, found -->") + row[0] + "<--";
					break;
				default:
					throw string("Expected 4 feilds, found ") + to_string(row.size());
			}	
		}

		void Task::TaskPrint(){
			cout 
			<< "<" << taskName << ">" 
			<< "<" << taskSlots << ">" 
			<< "<" << taskPass << ">"
			<< "<" << taskFail << ">\n";	
		}

		// writes the task data in graphviz format to a file
		void Task::TaskGraph(fstream& os){	
			if (!taskPass.empty())
				os << '"' << taskName << '"' << "->" << '"' << taskPass << '"' << "[color=green];\n";
			if (!taskFail.empty())
				os << '"' << taskName << '"' << "->" << '"' << taskFail << '"' << "[color=red];\n";
			if (taskFail.empty() && taskPass.empty())
				os << '"' << taskName << '"' << ";\n";
		} // TaskGraph

// contains (composition) a list of all task instances
	TaskManager::~TaskManager(){	}

		 TaskManager::TaskManager(vector< vector <string> >& csvData){
			int lineNumber = 0;
			for (auto row : csvData){
				try{
					lineNumber++;
					taskList.push_back(move(Task(row)));
				}
				catch (string& e){
					cerr << "Task could not understand line" << lineNumber << ": " << e << "\n";
				}
			}
		}

		void  TaskManager::TaskPrint(){
			int taskNumber = 0;
			for(auto t : taskList){
				taskNumber++;
				cout << "Task " << taskNumber << " ";
				t.TaskPrint();
			}
		}

		void  TaskManager::TaskGraph(string& filename){
			fstream os(filename + ".gv", ios::out);
			os << "digraph taskGraph {\n";
			for (auto t : taskList){
				t.TaskGraph(os);
			}
			os << "}|n";
			os.close();
			string cmd = string("dot -Tpng ") + filename + ".gv > " + filename + ".gv.png";
			cout << "running->" << cmd << "\n";
			system(cmd.c_str());
			cout << "\n";
		}		

		Task* TaskManager::TaskFind(string& name){
			for (size_t i = 0; i < taskList.size(); i++){
				if (taskList[i].getTaskName() == name)
					return &taskList[i];
			}
			return nullptr; // not found
		}

		void TaskManager::IntegrityCheck(){
			for (auto t : taskList){
				if (!t.getTaskPass().empty() && TaskFind(t.getTaskPass()) == nullptr)
					throw string("Task  '") + t.getTaskName() + "' referenced Pass task '" + t.getTaskPass() + "' but it does not exist";
				if (!t.getTaskFail().empty() && TaskFind(t.getTaskFail()) == nullptr)
					throw string("Task  '") + t.getTaskName() + "' referenced Fail task '" + t.getTaskFail() + "' but it does not exist";
			}
		}
