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
||   Implementation for Process Struct                           ||
 \_______________________________________________________________/
*/
#include <cstring>
#include <string>
#include "Process.h"

//I miss python generators
//Static memeber PIDNum acting as a PID Generator
int Process::PIDNum = 101;

/*
Function: Process (Default Constructor)

Use: Generates a blank process object with no default values set

Parameters: none
*/

Process::Process() {}

/*
Function: Process (Default Constructor)

Use: Generates a process from two lines of input.

Parameters: l1: Line of input expected to be in the form:
                ProcessName Priority ArrivalTime
			l2: Line of input expected to be in the form:
			    ProcessType ProcessTimer
			    Repeating ARRAY_SIZE number of times
*/

Process::Process(char * l1, char* l2) {
	//start tokenizing first line in the form "Processname Priority ArrivalTime"
	char * holder = strtok(l1, " ");
	ProcessName = holder;
	
	holder = strtok(nullptr, " ");
	Priority = atoi(holder);
	
	holder = strtok(nullptr, " ");
	ArrivalTime  = atoi(holder);
	
	//fill "History" array with values
	holder = strtok(l2, " ");
	
	for (int i = 0; i < ARRAY_SIZE && holder != nullptr; i++) {
		
		History[i][0] = holder[0];
		
		holder = strtok(nullptr, " ");
		History[i][1] = atoi(holder);
		
		holder = strtok(nullptr, " ");
	}
	
	//set all defaults to zero
	Sub = 0;
	CPUTimer = 0;
	IOTimer = 0;
	CPUTotal = 0;
	ITotal = 0;
	OTotal = 0;
	CPUCount = 0;
	ICount = 0;
	OCount = 0;
	
	//obtain pid & set PIDNum for next process obejct
	ProcessID = PIDNum;
	PIDNum++;
	
	LastTimeSeen = 0;
	TimeSpentWaiting = 0;
}
/*
Function: SingleClockTick, Process

Use: Decrements and Increments Timer and Totals respectively
     based on what is in the History[Sub][0] posititon

Parameters: none

Returns: Nothing
*/
void Process::SingleClockTick() {
	switch (History[Sub][0]) 
	{
		case 'C':
			CPUTimer--;
			CPUTotal++;
			break;
		case 'I':
			IOTimer--;
			ITotal++;
			break;
		case 'O':
			IOTimer--;
			OTotal++;
			break;
	}
}