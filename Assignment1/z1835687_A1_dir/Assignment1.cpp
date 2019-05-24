/*
  _______________________________________________________________
 /                                                               \
||  Course: CSCI-480    Assignment #: 1    Semester: Spring 2019 ||
||                                                               ||
||  NAME:  Aaron Fosco    Z-ID: z1835687     Section: 1          ||
||                                                               ||
||  TA's Name: Joshua Boley                                      ||
||                                                               ||
||  Due: Friday 1/25/2019 by 11:59PM                             ||
||                                                               ||
||  Description:                                                 ||
||                                                               ||
||   This is a simple program that mainly tests the fork()       ||
||   and wait() system calls.                                    ||
 \_______________________________________________________________/
*/

#include <unistd.h>
#include <sys/wait.h>
#include <iostream>

using namespace std;

/*
Funtion: Main

Use: Executes program

Parameters: none

Returns: 0: Regular exit
        -1: Failing to generate a new child process
*/

int main()
{
	cerr << "I am the original process. My PID is " << getpid() << "And my parent's PID is " << getppid() << endl;
	
	cerr << "Now we have the first fork!\n";
	pid_t pid = fork();
	
	// parent
	if (pid > 0)
	{
		
		cerr << "I am the Parent. My PID is " << getpid() << " and my parent's PID is " << getppid() << endl;
		sleep(2);
		
		cerr << "I am the Parent, about to call ps.\n";
		system("ps");
		wait(0);
		
		cerr << "I am the Parent, about to exit.\n";
		exit(0);
		
	}
	//child
	else if (pid == 0)
	{
		
		cerr << "I am the Child. My PID is " << getpid() << " and my parent's PID is " << getppid() << endl;
		
		cerr << "Now we have the second fork!\n";
		pid_t pid2 = fork();
		
		// 'parent' (child)
		if (pid2 > 0)
		{
			
			cerr << "I am still the Child. My PID is " << getpid() << " and my parent's PID is " << getppid() << endl;
			
			wait(0);
			
			cerr << "I am the Child, about to exit.\n";
			exit(0);
			
		}
		// 'child' (grand child)
		else if (pid2 == 0)
		{
			
			cerr << "I am the Grandchild. My PID is " << getpid() << " and my parent's PID is " << getppid() << endl;
			
			cerr << "I am the Grandchild, about to ext.\n";
			exit(0);
			
		}
		else if (pid2 == -1)
		{
			
			cerr << "The second fork failed!\n";
			exit(-1);
			
		}
	} 
	else if (pid == -1)
	{
		
		cerr << "The first fork failed!";
		exit(-1);
		
	}
	
	return 0;
}
