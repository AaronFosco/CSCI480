/*
  _______________________________________________________________
 /                                                               \
||  Course: CSCI-480    Assignment #: 4    Semester: Spring 2019 ||
||                                                               ||
||  NAME:  Aaron Fosco    Z-ID: z1835687     Section: 1          ||
||                                                               ||
||  TA's Name: Joshua Boley                                      ||
||                                                               ||
||  Due: Tuesday 3/12/2019 by 11:59PM                            ||
||                                                               ||
||  Description:                                                 ||
||   This program will Simulate Priority scheduling of processes ||
||   In a single processer system.                               ||
||   *****Note*****                                              ||
||     The flow of the program may be flawed as a process can    ||
||     Theortically go from                                      ||
||     Entry->Ready->Active->I/O queue->I/OActive->Ready         ||
||     In a single clock tick.                                   ||
 \_______________________________________________________________/
*/

#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <string>
#include <queue>

#include "Process.h"
#include "Assignment4.h"

using namespace std;

//Function prototypes

void FillEntry();
bool isFinished();
int howManyInSystem();
void PrintStatus();
void Terminate(Process*);

//Input file name
//const char* fileName = "data4.txt";
const char* fileName = "/home/turing/t90hch1/csci480/Assign4/data4.txt";

//specialized priority queue
typedef priority_queue<Process, vector<Process>, GreaterPriorityOperator> ProcessPriorityQueue;

//regular entry queue
queue<Process> Entry;

//P queue objects
ProcessPriorityQueue Ready;
ProcessPriorityQueue Input;
ProcessPriorityQueue Output;

//Process pointers
Process* Active = nullptr;
Process* IActive = nullptr;
Process* OActive = nullptr;

//Process holders for Processers that are currently doing work
Process PushHolder;
Process APHolder;
Process IPHolder;
Process OPHolder;

//other Important global variables
int Timer = 0;
int NoTermProcess = 0;

/*
Function: Main

Use: Main program entry point

Parameters:none

Returns: 0 on sucess
        -1 on file open error
*/

int main()
{
	//fill the Entry queue and initalize varables
	FillEntry();
	Timer = 0;
	bool waitProcessExsists = true;
	
	cout << "Simulation of Priority Scheduling\n\n";
	
	//Main run loop
	do
	{
		//retrive waiting processes if we can do so
		while (howManyInSystem() < AT_ONCE && waitProcessExsists) 
		{
			//Hold the Entering prcoess, and pop it off entry
			PushHolder = Entry.front();
			Entry.pop();
			
			//print step
			cout << "Process " 
				 << Entry.front().ProcessID 
				 << " moved from Entry Queue into the Ready Queue at time "
				 << Timer
				 << "\n\n";
			
			//set default for start time, and start "LastTimeSeen" (wait-time)
			PushHolder.LastTimeSeen = Timer;
			PushHolder.StartTime = Timer;
			
			//Push process onto ready queue
			Ready.push(PushHolder);
			
			//Make sure not to enter "stop here", or a process that has yet to arrive
			waitProcessExsists = !(Entry.front().ArrivalTime > Timer ||
								   Entry.front().ProcessName == "STOPHERE");
		}
		
		//Check Active pointer and Ready queue
		if (Active == nullptr && !Ready.empty())
		{
			//get process from Ready to pop() & set Active pointer
			APHolder = Ready.top();
			Active = &APHolder;
			Ready.pop();
			
			//Calculate (Total)TimeSpentWait
			Active->TimeSpentWaiting += (Timer - Active->LastTimeSeen);
			
			//Start CPUTimer countdown
			Active->CPUTimer = (short) Active->History[Active->Sub][1];
		}
		
		//If a process was active, add a clock tick
		if (Active != nullptr)
		{
			//Execute a clock tick based on where we are in History[Sub][0]
			Active->SingleClockTick();
			
			//is the CPU burst finished?
			if (Active->CPUTimer == 0) 
			{
				//increment CPU Burst Counter
				Active->CPUCount++;
				
				//increment subscript for History
				Active->Sub++;
				
				
				//What to do with process next?
				switch(Active->History[Active->Sub][0])
				{
					//Next step is Input
					case 'I':
						Input.push(*Active);
						break;
					//Next step is Output
					case 'O':
						Output.push(*Active);
						break;
					//Next step is Terminate
					default:
						Terminate(Active);
				}
				//Update LastTimeSeen for TimeSpentWaiting
				Active->LastTimeSeen = Timer;
				
				//Remove process from Ready & free our active pointer
				Active = nullptr;
			}
		}
		//Idle time!
		else
		{
			cout << "\nAt time " 
				 << Timer
				 << ", Active is 0, so we have idle time for a while\n\n";
		}
		
		//Get a I process if we can
		if (IActive == nullptr && !Input.empty())
		{
			//get process from Input to pop() & set IActive pointer
			IPHolder = Input.top();
			IActive = &IPHolder;
			Input.pop();
			
			//Calculate (Total)TimeSpentWait
			IActive->TimeSpentWaiting += (Timer - IActive->LastTimeSeen);
			
			//Start IOTimer countdown
			IActive->IOTimer = (short) IActive->History[IActive->Sub][1];
		}
		
		if (IActive != nullptr)
		{
			//Execute a clock tick based on where we are in History[Sub][0]
			IActive->SingleClockTick();
			
			//Are we done with our I Burst?
			if (IActive->IOTimer == 0)
			{
				//Increment In Burst counter
				IActive->ICount++;
				
				//increment our history subscript
				IActive->Sub++;
				
				//update LastTimeSeen (Wait Timer)
				IActive->LastTimeSeen = Timer;
				
				//Push back onto to Ready
				Ready.push(*IActive);
				
				//Our Input is now free again
				IActive = nullptr;
			}
		}
		
		if (OActive == nullptr && !Output.empty())
		{
			//get process from Output to pop() & set OActive pointer
			OPHolder = Output.top();
			OActive = &OPHolder;
			Output.pop();
			
			//Calculate (Total)TimeSpentWait
			OActive->TimeSpentWaiting += (Timer - OActive->LastTimeSeen);
			
			//Start IOTimer countdown
			OActive->IOTimer = (short) OActive->History[OActive->Sub][1];
		}
		
		if (OActive != nullptr)
		{
			//Execute a clock tick based on where we are in History[Sub][0]
			OActive->SingleClockTick();
			
			//Are we done with our O Burst?
			if (OActive->IOTimer == 0)
			{
				//Increment out Burst counter
				OActive->OCount++;
				
				//increment our history subscript
				OActive->Sub++;
				
				//update LastTimeSeen (Wait Timer)
				OActive->LastTimeSeen = Timer;
				
				//Push back onto to Ready
				Ready.push(*OActive);
				
				//Our Output is now free again
				OActive = nullptr;
			}
		}
		
		
		//output status when Timer is a multiple of HOW_OFTEN
		if ((Timer % HOW_OFTEN) == 0)
			PrintStatus();
		
		//Increment clock tick
		Timer++;
		
		//Make sure not to enter "stop here"
		waitProcessExsists = !(Entry.front().ArrivalTime > Timer ||
							   Entry.front().ProcessName == "STOPHERE");
		
	} while (!isFinished());
	
	//Final output
	cout << "\n\nThe run has ended\n"
		 << "The Final Value of the Timer was: "
		 << Timer << endl
		 << "Number of terminated Processes = "
		 << NoTermProcess << endl
		 << "Final ";
	
	//Final Print
	PrintStatus();
	
	return 0;
}

/*
Function: howManyInSystem

Use: Counts how many processes are in the system currently

Parameters: None

Returns: The number of processes in the system
*/

int howManyInSystem()
{
	int rv = (Ready.size() + Input.size() + Output.size());
	if (Active != nullptr)
		rv++;
	if (IActive != nullptr)
		rv++;
	if (OActive != nullptr)
		rv++;
	return rv;
}

/*
Function: isFinished

Use: Checks to see if the program should be done executing

Parameters: None

Returns: True if there are no more processes left, or we've reached MAX_TIME
         False otherwise
*/

bool isFinished() 
{
	return (Timer == MAX_TIME || 
			(Ready.empty() && 
			 Input.empty() && 
			 Output.empty() && 
			 Active == nullptr && 
			 IActive == nullptr && 
			 OActive == nullptr));
}

/*
Function: FillEntry

Use: Fills the Entry array with processes

Parameters: None

Returns: nothing
*/

void FillEntry() 
{
	//attempt to open file
	ifstream inFile;
	inFile.open(fileName);
	
	//exit on inFile error
	if (!inFile) {
		cerr << "unable to open input file";
		exit(-1);
	}
	
	//read two lines at a time
	char cline1[256];
	char cline2[256];
	
	//Null out two lines
	memset(cline1, '\0', 256);
	memset(cline2, '\0', 256);
	
	//read loop
	while (inFile && inFile.peek() != -1) {
		
		//carriage return and newline at the beginning of a newline
		//indicates we may be at the end of the file...
		if (inFile.peek() == '\n' || inFile.peek() == '\r')
			inFile.ignore();
		else
		{
			//read two lines
			inFile.getline(cline1, 256);
			inFile.getline(cline2, 256);
			
			//Generate a new process from the two read lines and push it onto Entry
			Entry.push(Process(cline1, cline2));
			
			//Null out the two lines
			memset(cline1, '\0', 256);
			memset(cline2, '\0', 256);
		}
	}
	
	//close file
	inFile.close();
}

/*
Function: PrintStatus

Use: Prints the status of all pointers & queues at a given moment

Parameters: None

Returns: Nothing
*/

void PrintStatus() 
{
	//holder variables
	queue<Process> tempq;
	ProcessPriorityQueue temppq;
	
	cout << "Status at time " << Timer << endl;
	cout << "Active is at " << ((Active == nullptr)? 0 : Active->ProcessID) << endl;
	cout << "IActive is at " << ((IActive == nullptr)? 0 : IActive->ProcessID) << endl;
	cout << "OActive is at " << ((OActive == nullptr)? 0 : OActive->ProcessID) << endl;
	
	
	cout << "Contents of the Entry Queue:" << endl;
	
	//Print everyhing in Empty
	while (!Entry.empty())
	{
		if (Entry.front().ProcessName != "STOPHERE")
			cout << Entry.front().ProcessID
				 << " Priority = "
				 << Entry.front().Priority
				 << " arriving at time = "
				 << Entry.front().ArrivalTime
				 << endl;
		
		tempq.push(Entry.front());
		Entry.pop();
	}
	
	//'refill' Entry
	Entry = tempq;
	
	//empty out our temp queue
	while (!tempq.empty())
		tempq.pop();
	
	cout << "Contents of the Ready Queue:" << endl;
	
	//Print everything in Ready with ProcessID & Priority
	if (Ready.empty())
		cout << "(Empty)";
	else
	{
		while (!Ready.empty())
		{
			cout << Ready.top().ProcessID
				 << "("
				 << Ready.top().Priority
				 << ")   ";
			
			temppq.push(Ready.top());
			Ready.pop();
		}
		
		//'refill' Ready
		Ready = temppq;
		
		//empty out our temp priority queue
		while (!temppq.empty())
			temppq.pop();
	}
	cout << endl;
	
	
	cout << "Contents of the Input Queue:" << endl;
	
	//Print everything in Input with ProcessID & Priority
	if (Input.empty())
		cout << "(Empty)";
	else
	{
		while (!Input.empty())
		{
			cout << Input.top().ProcessID
				 << "("
				 << Input.top().Priority
				 << ")   ";
			
			temppq.push(Input.top());
			Input.pop();
		}
		
		//'refill' Input
		Input = temppq;
		
		//empty out our temp priority queue
		while (!temppq.empty())
			temppq.pop();
	}
	cout << endl;
	
	cout << "Contents of the Output Queue:" << endl;
	
	//Print everything in Output with ProcessID & Priority
	if (Output.empty())
		cout << "(Empty)";
	else
	{
		while (!Output.empty())
		{
			cout << Output.top().ProcessID
				 << "("
				 << Output.top().Priority
				 << ")   ";
			
			temppq.push(Output.top());
			Output.pop();
		}
		
		//'refill' Output
		Output = temppq;
		
		//empty out our temp priority queue
		while (!temppq.empty())
			temppq.pop();
	}
	
	//padding
	cout << "\n\n";
}

/*
Function: Terminate

Use: Prints out a process's Stats and increments Terminate counter

Parameters: x: a pointer to a process

Returns: Nothing
*/

void Terminate(Process* x)
{
	cout << "\nA Process has terminated.\n";
	cout << setw(22) << left << "Process ID:";
	cout << x->ProcessID << endl;
	cout << setw(22) << left << "Name:";
	cout << x->ProcessName << endl;
	cout << setw(22) << left << "Priority:";
	cout << x->Priority << endl;
	cout << setw(22) << left << "Started at time:";
	cout << x->StartTime << " and ended at time " << Timer << endl;
	cout << setw(22) << left << "Total CPU time:";
	cout << x->CPUTotal << " in " << x->CPUCount << " CPU Burst(s)" << endl;
	cout << setw(22) << left << "Total Input time:";
	cout << x->ITotal << " in " << x->ICount << " Input Burst(s)" << endl;
	cout << setw(22) << left << "Total Output time:";
	cout << x->OTotal << " in " << x->OCount << " Output Burst(s)" << endl;
	cout << setw(22) << left << "Time spend waiting:";
	cout << x->TimeSpentWaiting << "\n\n";
	
	NoTermProcess++;
}








