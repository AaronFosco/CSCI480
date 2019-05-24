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
||   Process struct declarations                                 ||
 \_______________________________________________________________/
*/
#ifndef PROCESS_H
#define PROCESS_H
#include <string>
#include "Assignment4.h"


struct Process;
struct GreaterPriorityOperator;

/*
Struct: Process

Use: Represents a logical process that may need
     CPU, Input, and/or Output Bursts along with
	 Statistics to go along with each
*/

struct Process 
{
	Process(char*, char*);
	Process();
	void SingleClockTick();
	static int PIDNum;
	std::string ProcessName;
	int Priority;
	int ProcessID;
	int ArrivalTime;
	int StartTime;
	char History[ARRAY_SIZE][2];
	short int Sub;
	short int CPUTimer;
	short int IOTimer;
	short int CPUTotal;
	short int ITotal;
	short int OTotal;
	short int CPUCount;
	short int ICount;
	short int OCount;
	int LastTimeSeen;
	int TimeSpentWaiting;
};

/*
Struct: GreaterPriorityOperator 

Use: A sorting Struct used for sorting operations on a 
     Data structure of type Process.

Example:
typedef priority_queue<Process, vector<Process>, GreaterPriorityOperator> ProcessPriorityQueue;
*/

struct GreaterPriorityOperator 
{
	bool operator()(const Process& lhs, const Process& rhs) const 
	{
		if (lhs.Priority == rhs.Priority)
			return (lhs.LastTimeSeen) > (rhs.LastTimeSeen);
		else
			return lhs.Priority < rhs.Priority;
	}
};

#endif