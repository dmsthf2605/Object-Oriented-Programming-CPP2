/*
OOP345 Milestone 2
Name           : Eunsol Lee
Date           : November 13, 2016(Sun)
Student Number : 029-557-154
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "util.h"

using namespace std;

// task name starts with an alpha or _ character
// followd by alphas, digits, spaces, '-' or '_'
bool taskNameValid(string& s){
	// name cannot be empty string ""
	if(s.empty()) return false;
	for(auto chr : s){
		if(!(isalnum(chr) || chr == ' ' || chr == '_'))
			return false;
	}
	return true;
}

// field slot is an integer ( one or more digits 0-9)
bool taskSlotValid(string& s){
	for(auto chr : s){
		if(!(isdigit(chr)))
			return false;
	}
	return true;
}

// the instance of a task, parasing, printing, graphing
class Task{
	// Field 1,3, and 4 are task names
	string taskName, taskSlots, taskAccept, taskFail;

	public:
		~Task(){ }

		// if there is only 1 field, 'slots' defaults to "1"
		Task(vector<string>& row) : taskSlots("1"){
			switch(row.size()){
				case 4:
					if(taskNameValid(row[3]))
						taskFail = row[3];
					else 
						throw string("expected fail task name, found -->") + row[3] + "<--";
				case 3:
					if(taskNameValid(row[2]))
						taskAccept = row[2];
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

		void TaskPrint(){
			cout 
			<< "<" << taskName << ">" 
			<< "<" << taskSlots << ">" 
			<< "<" << taskAccept << ">" 
			<< "<" << taskFail << ">\n";	
		}

		// writes the task data in graphviz format to a file
		void TaskGraph(fstream& os){
			if (!taskFail.empty())
				os << '"' << taskName << '"' << "->" << '"' << taskFail << '"' << ";\n";	
			if (!taskAccept.empty())
				os << '"' << taskName << '"' << "->" << '"' << taskAccept << '"' << ";\n";	
			if (taskFail.empty() && taskAccept.empty())
				os << '"' << taskName << '"' << ";\n";
		} // TaskGraph
};

// contains (composition) a list of all task instances
class TaskManager{
	vector<Task> taskList;
	
	public:
		~TaskManager(){	}

		TaskManager(vector< vector <string> >& csvData){
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

		void TaskPrint(){
			int taskNumber = 0;
			for(auto t : taskList){
				taskNumber++;
				cout << "Task " << taskNumber << " ";
				t.TaskPrint();
			}
		}

		void TaskGraph(string& filename){
			fstream os(filename + ".gv", ios::out);
			os << "digraph taskGraph {\n";
			for (auto t : taskList){
				t.TaskGraph(os);
			}
			os << "}|n";
			os.close();
			string cmd = string("dot -Tpng ") + filename + ".gv > " + filename + ".gv.png";
			system(cmd.c_str());
		}		
};

int main(int argc, char** argv){
	string filename;
	char delimeter;

	if (argc != 3){
		std::cerr << "Usage: " << argv[0] << " taskfile.dat(a csv file) delimeter-char\n";
		return 1;
	}

	if (argc > 1) filename = argv[1];
	if (argc > 2) delimeter = argv[2][0];

	std::vector< std::vector <std::string> > csvTaskData;

	csvRead(filename, delimeter, csvTaskData);

	// csvPrint(csvTaskData);

	TaskManager tm(csvTaskData);
	tm.TaskPrint();
	tm.TaskGraph(filename);

	return 0;
} // main()
