/*
OOP345 Milestone 5
Name           : Eunsol Lee
Date           : December 8th(Thursday)
Student Number : 029-557-154
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>

#include "util.h"
#include "i.h"
#include "o.h"
#include "t.h"
#include "job.h"
#include "machine.h"

using namespace std;

// Factory has a list of Machines, one machine per Task. 
class Factory{
	vector<Machine> machineList;

public:
	Factory(ItemManager& im, OrderManager& om, TaskManager& tm){
		srand(time(0)); //initialize the random number generator with the time of day clock

		// ** STEP 1 Create a factory consisting of a network of machines, one machine per task **
		cout << "tm.getSize() = " << tm.getSize() << "\n";

		for (size_t t = 0; t < tm.getSize(); t++){
			machineList.push_back(move(Machine(tm.getTask(t))));
		}

		// Print out the list of machines
		/*int linenum = 0;
		  for (auto m : machineList){
		  linenum++;
		  cout << linenum << ": '" << m.getTaskName() << "'\n";
		  }
		  */

		// ** STEP 2 Find the source node in machine (task) graph **
		auto MachineFind = [&](string& name) -> Machine*
		{
			for (size_t i = 0; i < machineList.size(); i++){
				if (machineList[i].getTaskName() == name)
					return &machineList[i];
			}
			return nullptr; // not found
		};

		// increment the counter for Machine Pass and Fail
		for (auto m : machineList){
			string pass = m.getTaskPass();
			if (!pass.empty()) MachineFind(pass)->incinBoundCount();

			string fail = m.getTaskFail();
			if (!fail.empty()) MachineFind(fail)->incinBoundCount();
		}

		int linenum = 0;
		int source = -1;
		for (size_t m = 0; m < machineList.size(); m++){
			linenum++;
			cout << linenum << ": '" << machineList[m].getTaskName() << "'";
			if (machineList[m].isSingleton()){
				cout << " SINGLETON";
			}
			else {
				if (machineList[m].isSource()){
					cout << " *SOURCE*";
					if (source == -1){ // first source
						source = m;
					}
					else {
						throw string("Multiple sources. Fix data and re-submit!\n");
					}
				}
				if (machineList[m].isSink()) cout << " SINK";
			}
			cout << "\n";
		}

		// ** STEP 3 Load all the jobs into the job queue for the source machine **
		cout << "\n** Source machine is " << source << " **\n\n";

		if (source == -1)
			throw string("No source node. Fix datat and re-submit!\n");

		for (size_t o = 0; o < om.getSize(); o++) {
			machineList[source].AddJob(std::move(Job(om.getOrder(o))));
		}

		// Print out the job queue size for each machine
		// The source machine should have all the jobs
		// The other machine input queues should be empty
		linenum = 0;
		for (auto m : machineList){
			linenum++;
			cout << linenum << ": " << m.getTaskName() << " has " << m.inputQSize() << " jobs\n";
		}
		cout << "\n";

		for (auto &m : machineList){
			m.Classify(im);
		}
		cout << "\n";

		// ** STEP 4 Time loop **
		int time = 0;		
		while (true){
			cout << "TIME = " << time << "\n";

			// ** STEP 5 Any machine have something in its input Q? **
			bool AllDone = true;
			for (auto m : machineList){
				if (m.inputQSize()){ // found a machine with some jobs
					AllDone = false;
					break;
				}
			}

			if (AllDone){ // break out of time loop
				cout << "\n**All DONE!**\n";
				break;
			}

			cout << "\nNot all done yet!\n\n";

			// ** STEP 6 MACHINE LOOP - for each machine --- **
			for (auto &m : machineList){

				// ** STEP 7 Input Q Empty? **
				if (m.inputQSize() == 0){ // when queue is empty, there is nothing to do
					continue; // go process next machine
				}

				// ** STEP 8 Remove job from the input Q **
				// something to do!
				Job job = move(m.getJob());
				cout << m.getTaskName() << " will work on job "
					<< job.getCustomerName() << "/"
					<< job.getProductName() << "\n";

				// ** STEP 9 Sink? **
				if (m.isSink()){
					cout << job.getCustomerName() << "/" << job.getProductName()
						<< " is DONE!\n";
					continue; // go process next machine
				}

				bool didSomething = false;
				
				// ** STEP 10 Install Item? **
				if (m.getInstaller()){
					// do they need out servicies
					cout << "'" << m.getTaskName() << "' is an installer\n";

					// for each item in the job that is not installed,
					// look up the installer name from the item data
					// If the installer name matches task name -> Installer(i, true)
					for (size_t i = 0; i < job.size(); i++){
						if (job.Installed(i)) // alreaay installed
						continue;

						// ** STEP 11 Install item **
						string itemName = job.getItem(i);
						Item* itemPtr = im.ItemFind(itemName);
						if (m.getTaskName() == itemPtr->getItemInstallerTask()){
							job.Installed(i, true); // flag the item as installed
							didSomething = true;
							time++;
							cout << "'" << m.getTaskName() << "' installed '" << itemName << "'\n\n";
							break; // all done installing 1 item
						}
					}
				}

				// ** STEP 12 Remove Item? **
				if (m.getRemover()){
					//do they need our services
					cout << "'" << m.getTaskName() << "' is an remover\n";

					// for eah item in the job that is no installed,
					// look for a item that is installed that uses task as a remover
					for (int i = job.size() - 1; i >= 0; i--){ // backwards
						if (!job.Installed(i))
							continue; // not installed

						// ** STEP 13 Remove Item **
						string itemName = job.getItem(i);
						Item* itemPtr = im.ItemFind(itemName);
						if (m.getTaskName() == itemPtr->getItemRemoverTask()){
							job.Installed(i, false); // flag the item as removed
							didSomething = true;
							time++;
							cout << "'" << m.getTaskName() << "' removed '" << itemName << "'\n\n";
							break; // all done removing 1 item
						}
					}
				}
				
				auto MovePass = [&] {
					string pass = m.getTaskPass();
					cout << "moving job to pass machine '" << pass << "'\n";
					for (auto &m2 : machineList){
						if (m2.getTaskName() == pass){
							m2.AddJob(job);
							break;
						}
					}
				};

				auto MoveFail = [&] {
					string fail = m.getTaskFail();
					cout << "moving job to fail machine '" << fail << "'\n";
					for (auto &m2 : machineList){
						if (m2.getTaskName() == fail){
							m2.AddJob(job);
							break;
						}
					}
				};

				if (!didSomething){
					// move job to passed inputQ
					MovePass();
					continue; // end of this machine
				}

				// ** STEP 14 Inspector**
				// if there is only a Pass task
				if (m.getTaskFail().empty()){
					// move job to passed inputQ
					MovePass();
					continue;
				}

				// flip a coin (rand() &1 --- test if odd)
				if (rand() & 1){ // pass
					// move job to Pass machine inputQ
					MovePass();
					continue;
				}
				else { // fail
					// move job to Fail machine inputQ
					MoveFail();
					continue;
				}
			} // machine loop
		} // end time loop

		cout << "--- SIMULATION OVER ---\n";
		cout << "TIME = " << time << "\n";	
	}
};

int main(int argc, char** argv){

	string filename;
	//char delimeter;

	try{
		if (argc != 5)
			std::cerr << "Usage: " << argv[0] << " itemfile.dat orderfile.dat taskfile.dat(all csv file) delimiter-char\n";

		string filenameItem  = argv[1]; // 1st arg
		string filenameOrder = argv[2]; // 2nd arg
		string filenameTask  = argv[3]; // 3rd arg
		char delim           = argv[4][0]; // 4th, 1st char

		std::vector< std::vector <std::string> > csvItemData;
		std::vector< std::vector <std::string> > csvOrderData;
		std::vector< std::vector <std::string> > csvTaskData;

		csvRead(filenameItem, delim, csvItemData);
		csvRead(filenameOrder, delim, csvOrderData);
		csvRead(filenameTask, delim, csvTaskData);

		// csvPrint(csvItemData);

		ItemManager im(csvItemData);
		im.ItemPrint();
		im.ItemGraph(filenameItem);

		OrderManager om(csvOrderData);
		om.OrderPrint();
		om.OrderGraph(filenameOrder);

		TaskManager tm(csvTaskData);
		tm.TaskPrint();
		tm.TaskGraph(filenameTask);


		bool GoodToGo = true;
		cout << "Checking Task Integrity\n";
		try{
			tm.IntegrityCheck();
		}
		catch (string& e){
			GoodToGo = false;
			cerr << e << "\n";
		}

		cout << "Checking Item Integrity\n";
		try{
			im.IntegrityCheck(tm);
		}
		catch (string& e){
			GoodToGo = false;
			cerr << e << "\n";
		}

		cout << "Checking Order Integrity\n";
		try{
			om.IntegrityCheck(im);
		}
		catch (string& e){
			GoodToGo = false;
			cerr << e << "\n";
		}

		if (!GoodToGo){
			cerr << "\n*******************************\n";
			cerr << "*Data errors. Fix and resubmit.*\n";
			cerr << "*******************************\n\n";
			exit(1);
		}

		cerr << "\n************************************\n";
		cerr << "*No Data errors. We are good to go.*\n";
		cerr << "************************************\n\n";

		Factory factory(im, om, tm);
	}
	catch (string& e){
		cerr << e << "\n";
	}

	return 0;
}
