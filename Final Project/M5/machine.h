/*
OOP345 Milestone 5
Name           : Eunsol Lee
Date           : December 8th(Thursday)
Student Number : 029-557-154
*/

#pragma once
#include "t.h"
#include <queue> // std::queue

class Machine : public Task
{
	int inBoundCount; // count the number of in-coming edges
	std::queue<Job> inputQ; // queue of jobs waiting to  be processed by the machine
	bool bInstaller;
	bool bRemover;

public:
	Machine() : inBoundCount(0), bInstaller(false), bRemover(false){ }
	Machine(Task* t) : Task(*t), inBoundCount(0), bInstaller(false), bRemover(false){ }

	bool isSink(){ return getTaskPass().empty(); }
	bool isSource(){ return inBoundCount == 0; }
	bool isSingleton() { return isSink() && isSource(); }
	void incinBoundCount() { inBoundCount++; }
	void AddJob(Job j){ inputQ.push(std::move(j)); }
	
	size_t inputQSize() { return inputQ.size(); }
	Job getJob(){ // Use a std::move operation to move the job from the head of the input queue to a local variable ‘job’.
		Job job = move(inputQ.front()); 
		inputQ.pop(); 
		return job;
	}

	bool getInstaller(){ return bInstaller; }
	bool getRemover(){ return bRemover; }
	
	void Classify(ItemManager& im){ 
		bInstaller = false;
		bRemover = false;

		int n = 0;
		for (size_t i = 0; i < im.getSize(); i++){
			if (getTaskName() == im.getItem(i) -> getItemInstallerTask())
				bInstaller = true;
			if (getTaskName() == im.getItem(i) -> getItemRemoverTask())
				bRemover = true;
			if (bInstaller) cout << getTaskName() << " is an installer\n";
			if (bRemover) cout << getTaskName() << " is a Remover\n";		
			
		}
	}	
};
